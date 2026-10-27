#pragma once

#include <cstdint>

namespace e506::battery {

using Milliseconds = std::int64_t;

struct TemperatureSample {
    double celsius;
    Milliseconds timestamp_ms;
    bool acquisition_valid;
};

enum class State {
    Normal,
    CoolingRequested,
    ShutdownRequested
};

enum class Diagnostic {
    DegradedSensing,
    SensorFault,
    ResetRejected
};

class ITemperatureSensor {
public:
    virtual ~ITemperatureSensor() = default;
    virtual TemperatureSample read() = 0;
};

class IMonotonicClock {
public:
    virtual ~IMonotonicClock() = default;
    virtual Milliseconds nowMs() const = 0;
};

class ICoolingControl {
public:
    virtual ~ICoolingControl() = default;
    virtual void setEnabled(bool enabled) = 0;
};

class IShutdownControl {
public:
    virtual ~IShutdownControl() = default;
    virtual void setRequested(bool requested) = 0;
};

class IDiagnosticSink {
public:
    virtual ~IDiagnosticSink() = default;
    virtual void report(Diagnostic diagnostic) = 0;
};

class BatteryThermalSupervisor {
public:
    BatteryThermalSupervisor(ITemperatureSensor& first_sensor,
                             ITemperatureSensor& second_sensor,
                             const IMonotonicClock& clock,
                             ICoolingControl& cooling,
                             IShutdownControl& shutdown,
                             IDiagnosticSink& diagnostics);

    void evaluate();
    bool reset();
    State state() const noexcept;

private:
    enum class ObservationKind {
        PlausiblePair,
        SingleUsable,
        Fault
    };

    struct Observation {
        ObservationKind kind;
        double temperature_celsius;
    };

    Observation observe();
    void transitionTo(State next);

    ITemperatureSensor& first_sensor_;
    ITemperatureSensor& second_sensor_;
    const IMonotonicClock& clock_;
    ICoolingControl& cooling_;
    IShutdownControl& shutdown_;
    IDiagnosticSink& diagnostics_;
    State state_{State::Normal};
};

}  // namespace e506::battery
