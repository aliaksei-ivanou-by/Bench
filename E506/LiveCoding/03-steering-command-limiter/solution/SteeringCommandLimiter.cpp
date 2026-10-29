#include "SteeringCommandLimiter.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace e506::steering {
namespace {

constexpr double kMaximumAbsoluteTorqueNm = 3.0;
constexpr double kMaximumTorqueRateNmPerSecond = 50.0;
constexpr std::int64_t kMaximumCommandAgeMs = 50;

// Предусловие: timestamp_ms <= now_ms, а max_age_ms неотрицателен.
bool isStale(std::int64_t now_ms, std::int64_t timestamp_ms,
             std::int64_t max_age_ms) noexcept {
    return (timestamp_ms >= 0) ? ((now_ms - timestamp_ms) > max_age_ms)
                               : (now_ms > (timestamp_ms + max_age_ms));
}

// Вызывающая сторона уже проверила условие now_ms > previous_ms.
bool elapsedFits(std::int64_t now_ms, std::int64_t previous_ms) noexcept {
    return (previous_ms >= 0) ||
           (now_ms <= (std::numeric_limits<std::int64_t>::max() + previous_ms));
}

}  // namespace

SteeringCommandLimiter::SteeringCommandLimiter(
    ICommandSource& source,
    const IMonotonicClock& clock,
    ISteeringActuator& actuator,
    IDiagnosticSink& diagnostics,
    std::int64_t initial_time_ms)
    : source_(source),
      clock_(clock),
      actuator_(actuator),
      diagnostics_(diagnostics),
      last_accepted_time_ms_(initial_time_ms) {}

void SteeringCommandLimiter::tick() {
    const auto command = source_.read();
    if (!command) {
        diagnostics_.report(Diagnostic::MissingCommand);
        return;
    }

    const auto now_ms = clock_.nowMs();
    if ((now_ms <= last_accepted_time_ms_) ||
        !elapsedFits(now_ms, last_accepted_time_ms_)) {
        diagnostics_.report(Diagnostic::InvalidTime);
        return;
    }
    if (command->timestamp_ms > now_ms) {
        diagnostics_.report(Diagnostic::InvalidCommand);
        return;
    }
    if (isStale(now_ms, command->timestamp_ms, kMaximumCommandAgeMs)) {
        diagnostics_.report(Diagnostic::StaleCommand);
        return;
    }
    if (!std::isfinite(command->requested_torque_nm)) {
        diagnostics_.report(Diagnostic::InvalidCommand);
        return;
    }

    double limited_torque_nm = 0.0;
    if (!command->driver_override) {
        const auto elapsed_seconds =
            static_cast<double>(now_ms - last_accepted_time_ms_) / 1000.0;
        const auto maximum_delta_nm =
            kMaximumTorqueRateNmPerSecond * elapsed_seconds;
        limited_torque_nm = std::clamp(
            command->requested_torque_nm,
            last_accepted_torque_nm_ - maximum_delta_nm,
            last_accepted_torque_nm_ + maximum_delta_nm);
        limited_torque_nm = std::clamp(
            limited_torque_nm,
            -kMaximumAbsoluteTorqueNm,
            kMaximumAbsoluteTorqueNm);
    }

    if (!actuator_.applyTorque(limited_torque_nm)) {
        diagnostics_.report(Diagnostic::ActuatorRejected);
        return;
    }

    last_accepted_torque_nm_ = limited_torque_nm;
    last_accepted_time_ms_ = now_ms;
}

double SteeringCommandLimiter::lastAcceptedTorqueNm() const noexcept {
    return last_accepted_torque_nm_;
}

std::int64_t SteeringCommandLimiter::lastAcceptedTimeMs() const noexcept {
    return last_accepted_time_ms_;
}

}  // namespace e506::steering
