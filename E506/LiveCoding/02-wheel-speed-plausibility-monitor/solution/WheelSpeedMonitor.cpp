#include "WheelSpeedMonitor.h"

#include <cmath>

namespace e506::wheel_speed {
namespace {

constexpr double kMinimumSpeedMps = 0.0;
constexpr double kMaximumSpeedMps = 100.0;
constexpr double kMaximumDifferenceMps = 1.5;
constexpr std::int64_t kMaximumSampleAgeMs = 50;
constexpr std::uint32_t kBadCyclesBeforeDegraded = 3U;
constexpr std::uint32_t kGoodCyclesBeforeRecovery = 5U;

// Предусловие: timestamp_ms <= now_ms, а max_age_ms неотрицателен.
bool isStale(std::int64_t now_ms, std::int64_t timestamp_ms,
             std::int64_t max_age_ms) noexcept {
    return (timestamp_ms >= 0) ? ((now_ms - timestamp_ms) > max_age_ms)
                               : (now_ms > (timestamp_ms + max_age_ms));
}

bool isValidValue(double value) {
    return std::isfinite(value) && value >= kMinimumSpeedMps &&
           value <= kMaximumSpeedMps;
}

}  // namespace

WheelSpeedMonitor::WheelSpeedMonitor(ISpeedSensor& primary,
                                     ISpeedSensor& secondary,
                                     const IMonotonicClock& clock,
                                     IStatusOutput& output,
                                     IDiagnosticSink& diagnostics)
    : primary_(primary),
      secondary_(secondary),
      clock_(clock),
      output_(output),
      diagnostics_(diagnostics) {}

void WheelSpeedMonitor::tick() {
    const auto primary = primary_.read();
    const auto secondary = secondary_.read();
    if (!primary || !secondary) {
        degradeImmediately(Diagnostic::MissingSample);
        return;
    }

    const auto now_ms = clock_.nowMs();
    if (primary->timestamp_ms > now_ms || secondary->timestamp_ms > now_ms) {
        degradeImmediately(Diagnostic::InvalidSample);
        return;
    }
    if (isStale(now_ms, primary->timestamp_ms, kMaximumSampleAgeMs) ||
        isStale(now_ms, secondary->timestamp_ms, kMaximumSampleAgeMs)) {
        degradeImmediately(Diagnostic::StaleSample);
        return;
    }
    if (!isValidValue(primary->speed_mps) ||
        !isValidValue(secondary->speed_mps)) {
        degradeImmediately(Diagnostic::InvalidSample);
        return;
    }

    const bool plausible =
        std::fabs(primary->speed_mps - secondary->speed_mps) <=
        kMaximumDifferenceMps;

    if (status_ == Status::Available) {
        recovery_cycles_ = 0U;
        if (plausible) {
            bad_cycles_ = 0U;
            return;
        }
        ++bad_cycles_;
        if (bad_cycles_ >= kBadCyclesBeforeDegraded) {
            bad_cycles_ = 0U;
            enter(Status::Degraded);
        }
        return;
    }

    bad_cycles_ = 0U;
    if (!plausible) {
        recovery_cycles_ = 0U;
        return;
    }
    ++recovery_cycles_;
    if (recovery_cycles_ >= kGoodCyclesBeforeRecovery) {
        recovery_cycles_ = 0U;
        enter(Status::Available);
    }
}

Status WheelSpeedMonitor::status() const noexcept {
    return status_;
}

void WheelSpeedMonitor::enter(Status next) {
    if (next == status_) {
        return;
    }
    status_ = next;
    output_.publish(status_);
}

void WheelSpeedMonitor::degradeImmediately(Diagnostic diagnostic) {
    bad_cycles_ = 0U;
    recovery_cycles_ = 0U;
    diagnostics_.report(diagnostic);
    enter(Status::Degraded);
}

}  // namespace e506::wheel_speed
