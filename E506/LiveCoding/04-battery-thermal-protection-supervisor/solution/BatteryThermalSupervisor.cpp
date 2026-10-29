#include "BatteryThermalSupervisor.h"

#include <algorithm>
#include <cmath>

namespace e506::battery {
namespace {

constexpr double kMinimumTemperatureC = -40.0;
constexpr double kMaximumTemperatureC = 150.0;
constexpr double kMaximumDisagreementC = 5.0;
constexpr double kCoolingEnterC = 55.0;
constexpr double kCoolingExitC = 50.0;
constexpr double kShutdownC = 70.0;
constexpr std::int64_t kMaximumSampleAgeMs = 250;

// Предусловие: timestamp_ms <= now_ms, а max_age_ms неотрицателен.
bool isStale(std::int64_t now_ms, std::int64_t timestamp_ms,
             std::int64_t max_age_ms) noexcept {
    return (timestamp_ms >= 0) ? ((now_ms - timestamp_ms) > max_age_ms)
                               : (now_ms > (timestamp_ms + max_age_ms));
}

bool isUsable(const TemperatureSample& sample, std::int64_t now_ms) {
    return sample.acquisition_valid && std::isfinite(sample.celsius) &&
           sample.celsius >= kMinimumTemperatureC &&
           sample.celsius <= kMaximumTemperatureC &&
           sample.timestamp_ms <= now_ms &&
           !isStale(now_ms, sample.timestamp_ms, kMaximumSampleAgeMs);
}

}  // namespace

BatteryThermalSupervisor::BatteryThermalSupervisor(
    ITemperatureSensor& first_sensor,
    ITemperatureSensor& second_sensor,
    const IMonotonicClock& clock,
    ICoolingControl& cooling,
    IShutdownControl& shutdown,
    IDiagnosticSink& diagnostics)
    : first_sensor_(first_sensor),
      second_sensor_(second_sensor),
      clock_(clock),
      cooling_(cooling),
      shutdown_(shutdown),
      diagnostics_(diagnostics) {}

void BatteryThermalSupervisor::evaluate() {
    if (state_ == State::ShutdownRequested) {
        return;
    }

    const Observation observation = observe();
    if (observation.kind == ObservationKind::Fault) {
        diagnostics_.report(Diagnostic::SensorFault);
        transitionTo(State::ShutdownRequested);
        return;
    }
    if (observation.kind == ObservationKind::SingleUsable) {
        diagnostics_.report(Diagnostic::DegradedSensing);
    }

    const double temperature = observation.temperature_celsius;
    if (temperature >= kShutdownC) {
        transitionTo(State::ShutdownRequested);
    } else if (temperature >= kCoolingEnterC) {
        transitionTo(State::CoolingRequested);
    } else if (state_ == State::CoolingRequested &&
               temperature > kCoolingExitC) {
        return;
    } else {
        transitionTo(State::Normal);
    }
}

bool BatteryThermalSupervisor::reset() {
    if (state_ != State::ShutdownRequested) {
        return true;
    }

    const Observation observation = observe();
    if (observation.kind != ObservationKind::PlausiblePair ||
        observation.temperature_celsius > kCoolingExitC) {
        diagnostics_.report(Diagnostic::ResetRejected);
        return false;
    }

    transitionTo(State::Normal);
    return true;
}

State BatteryThermalSupervisor::state() const noexcept {
    return state_;
}

BatteryThermalSupervisor::Observation BatteryThermalSupervisor::observe() {
    const TemperatureSample first = first_sensor_.read();
    const TemperatureSample second = second_sensor_.read();
    const std::int64_t now_ms = clock_.nowMs();
    const bool first_usable = isUsable(first, now_ms);
    const bool second_usable = isUsable(second, now_ms);

    if (!first_usable && !second_usable) {
        return {ObservationKind::Fault, 0.0};
    }
    if (first_usable != second_usable) {
        return {ObservationKind::SingleUsable,
                first_usable ? first.celsius : second.celsius};
    }
    if (std::fabs(first.celsius - second.celsius) >
        kMaximumDisagreementC) {
        return {ObservationKind::Fault, 0.0};
    }
    return {ObservationKind::PlausiblePair,
            std::max(first.celsius, second.celsius)};
}

void BatteryThermalSupervisor::transitionTo(State next) {
    if (next == state_) {
        return;
    }

    if (state_ == State::CoolingRequested &&
        next != State::CoolingRequested) {
        cooling_.setEnabled(false);
    }
    if (state_ == State::ShutdownRequested &&
        next != State::ShutdownRequested) {
        shutdown_.setRequested(false);
    }
    if (state_ != State::CoolingRequested &&
        next == State::CoolingRequested) {
        cooling_.setEnabled(true);
    }
    if (state_ != State::ShutdownRequested &&
        next == State::ShutdownRequested) {
        shutdown_.setRequested(true);
    }

    state_ = next;
}

}  // namespace e506::battery
