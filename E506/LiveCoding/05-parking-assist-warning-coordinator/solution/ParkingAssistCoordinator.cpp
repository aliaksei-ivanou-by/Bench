#include "ParkingAssistCoordinator.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace e506::parking {
namespace {

constexpr double kMinimumDistanceM = 0.10;
constexpr double kMaximumDistanceM = 5.00;
constexpr double kCriticalMaximumM = 0.30;
constexpr double kNearMaximumM = 0.80;
constexpr double kCautionMaximumM = 1.50;
constexpr std::int64_t kMaximumSampleAgeMs = 200;

// Предусловие: timestamp_ms <= now_ms, а max_age_ms неотрицателен.
bool isStale(std::int64_t now_ms, std::int64_t timestamp_ms,
             std::int64_t max_age_ms) noexcept {
    return (timestamp_ms >= 0) ? ((now_ms - timestamp_ms) > max_age_ms)
                               : (now_ms > (timestamp_ms + max_age_ms));
}

Warning warningFor(double nearest_distance_m) {
    if (nearest_distance_m <= kCriticalMaximumM) {
        return Warning::Critical;
    }
    if (nearest_distance_m <= kNearMaximumM) {
        return Warning::Near;
    }
    if (nearest_distance_m <= kCautionMaximumM) {
        return Warning::Caution;
    }
    return Warning::Clear;
}

}  // namespace

ParkingAssistCoordinator::ParkingAssistCoordinator(
    IDistanceSensorProvider& sensors,
    const IMonotonicClock& clock,
    IWarningOutput& warnings,
    ICoverageOutput& coverage)
    : sensors_(sensors),
      clock_(clock),
      warnings_(warnings),
      coverage_output_(coverage) {}

void ParkingAssistCoordinator::evaluate() {
    const std::int64_t now_ms = clock_.nowMs();
    double nearest_distance_m = std::numeric_limits<double>::infinity();
    std::size_t usable_count = 0U;

    for (std::size_t index = 0U; index < kSensorCount; ++index) {
        const DistanceSample sample = sensors_.read(index);
        const bool timestamp_ordered =
            !last_accepted_timestamps_[index] ||
            sample.timestamp_ms >= *last_accepted_timestamps_[index];
        const bool usable =
            sample.acquisition_valid && std::isfinite(sample.distance_m) &&
            sample.distance_m >= kMinimumDistanceM &&
            sample.distance_m <= kMaximumDistanceM &&
            sample.timestamp_ms <= now_ms &&
            !isStale(now_ms, sample.timestamp_ms, kMaximumSampleAgeMs) &&
            timestamp_ordered;

        if (!usable) {
            continue;
        }

        ++usable_count;
        nearest_distance_m = std::min(nearest_distance_m, sample.distance_m);
        if (!last_accepted_timestamps_[index] ||
            sample.timestamp_ms > *last_accepted_timestamps_[index]) {
            last_accepted_timestamps_[index] = sample.timestamp_ms;
        }
    }

    const Warning next_warning = usable_count == 0U
                                  ? Warning::Unknown
                                  : warningFor(nearest_distance_m);
    const Coverage next_coverage = usable_count == kSensorCount
                                   ? Coverage::Full
                                   : Coverage::Degraded;
    publishIfChanged(next_warning, next_coverage);
}

Warning ParkingAssistCoordinator::warning() const noexcept {
    return warning_;
}

Coverage ParkingAssistCoordinator::coverage() const noexcept {
    return coverage_;
}

void ParkingAssistCoordinator::publishIfChanged(Warning next_warning,
                                                 Coverage next_coverage) {
    warning_ = next_warning;
    coverage_ = next_coverage;

    if (!last_published_warning_ || *last_published_warning_ != next_warning) {
        warnings_.publish(next_warning);
        last_published_warning_ = next_warning;
    }
    if (!last_published_coverage_ ||
        *last_published_coverage_ != next_coverage) {
        coverage_output_.publish(next_coverage);
        last_published_coverage_ = next_coverage;
    }
}

}  // namespace e506::parking
