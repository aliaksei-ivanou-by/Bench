#include "AebRequestGate.h"

#include <algorithm>
#include <cmath>

namespace e506::aeb {
namespace {

constexpr double kMinimumSpeedMps = 5.0;
constexpr double kMinimumConfidence = 0.90;
constexpr double kMaximumTimeToCollisionS = 1.20;
constexpr double kMaximumDecelerationMps2 = 8.0;
constexpr std::int64_t kMaximumSampleAgeMs = 100;

// Предусловие: timestamp_ms <= now_ms, а max_age_ms неотрицателен.
// Исключаем знаковое переполнение даже при крайних значениях времени.
bool isStale(std::int64_t now_ms, std::int64_t timestamp_ms,
             std::int64_t max_age_ms) noexcept {
    return (timestamp_ms >= 0) ? ((now_ms - timestamp_ms) > max_age_ms)
                               : (now_ms > (timestamp_ms + max_age_ms));
}

bool isValid(const PerceptionSample& sample) {
    return std::isfinite(sample.speed_mps) && sample.speed_mps >= 0.0 &&
           std::isfinite(sample.confidence) && sample.confidence >= 0.0 &&
           sample.confidence <= 1.0 &&
           std::isfinite(sample.time_to_collision_s) &&
           sample.time_to_collision_s >= 0.0 &&
           std::isfinite(sample.desired_deceleration_mps2) &&
           sample.desired_deceleration_mps2 >= 0.0;
}

}  // namespace

AebRequestGate::AebRequestGate(IPerceptionSource& source,
                               const IMonotonicClock& clock,
                               IBrakeActuator& actuator,
                               IDiagnosticSink& diagnostics)
    : source_(source),
      clock_(clock),
      actuator_(actuator),
      diagnostics_(diagnostics) {}

void AebRequestGate::tick() {
    const auto sample = source_.read();
    if (!sample) {
        diagnostics_.report(Diagnostic::MissingSample);
        return;
    }

    const auto now_ms = clock_.nowMs();
    if (sample->timestamp_ms > now_ms) {
        diagnostics_.report(Diagnostic::InvalidSample);
        return;
    }
    if (isStale(now_ms, sample->timestamp_ms, kMaximumSampleAgeMs)) {
        diagnostics_.report(Diagnostic::StaleSample);
        return;
    }
    if (!isValid(*sample)) {
        diagnostics_.report(Diagnostic::InvalidSample);
        return;
    }

    if (sample->driver_override || sample->speed_mps < kMinimumSpeedMps ||
        sample->confidence < kMinimumConfidence ||
        sample->time_to_collision_s > kMaximumTimeToCollisionS) {
        return;
    }

    const auto deceleration = std::clamp(
        sample->desired_deceleration_mps2, 0.0, kMaximumDecelerationMps2);
    if (!actuator_.requestDeceleration(deceleration)) {
        diagnostics_.report(Diagnostic::ActuatorRejected);
    }
}

}  // namespace e506::aeb
