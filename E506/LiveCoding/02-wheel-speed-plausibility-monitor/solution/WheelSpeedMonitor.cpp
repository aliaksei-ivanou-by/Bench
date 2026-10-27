#include "WheelSpeedMonitor.h"

#include <cmath>

namespace e506::wheel_speed {
namespace {

constexpr double kMinimumSpeedMps = 0.0;
constexpr double kMaximumSpeedMps = 100.0;
constexpr double kMaximumDifferenceMps = 1.5;
constexpr Milliseconds kMaximumSampleAgeMs = 50;
constexpr unsigned kBadCyclesBeforeDegraded = 3;
constexpr unsigned kGoodCyclesBeforeRecovery = 5;

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
    if (now_ms - primary->timestamp_ms > kMaximumSampleAgeMs ||
        now_ms - secondary->timestamp_ms > kMaximumSampleAgeMs) {
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
        recovery_cycles_ = 0;
        if (plausible) {
            bad_cycles_ = 0;
            return;
        }
        ++bad_cycles_;
        if (bad_cycles_ >= kBadCyclesBeforeDegraded) {
            bad_cycles_ = 0;
            enter(Status::Degraded);
        }
        return;
    }

    bad_cycles_ = 0;
    if (!plausible) {
        recovery_cycles_ = 0;
        return;
    }
    ++recovery_cycles_;
    if (recovery_cycles_ >= kGoodCyclesBeforeRecovery) {
        recovery_cycles_ = 0;
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
    bad_cycles_ = 0;
    recovery_cycles_ = 0;
    diagnostics_.report(diagnostic);
    enter(Status::Degraded);
}

}  // namespace e506::wheel_speed
