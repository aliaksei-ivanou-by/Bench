#pragma once

#include <cstdint>
#include <optional>

namespace e506::wheel_speed {


struct SpeedSample {
    double speed_mps;
    std::int64_t timestamp_ms;
};

enum class Status {
    Available,
    Degraded
};

enum class Diagnostic {
    MissingSample,
    StaleSample,
    InvalidSample
};

class ISpeedSensor {
public:
    virtual ~ISpeedSensor() = default;
    virtual std::optional<SpeedSample> read() = 0;
};

class IMonotonicClock {
public:
    virtual ~IMonotonicClock() = default;
    virtual std::int64_t nowMs() const = 0;
};

class IStatusOutput {
public:
    virtual ~IStatusOutput() = default;
    virtual void publish(Status status) = 0;
};

class IDiagnosticSink {
public:
    virtual ~IDiagnosticSink() = default;
    virtual void report(Diagnostic diagnostic) = 0;
};

class WheelSpeedMonitor {
public:
    WheelSpeedMonitor(ISpeedSensor& primary,
                      ISpeedSensor& secondary,
                      const IMonotonicClock& clock,
                      IStatusOutput& output,
                      IDiagnosticSink& diagnostics);

    void tick();
    Status status() const noexcept;

private:
    void enter(Status next);
    void degradeImmediately(Diagnostic diagnostic);

    ISpeedSensor& primary_;
    ISpeedSensor& secondary_;
    const IMonotonicClock& clock_;
    IStatusOutput& output_;
    IDiagnosticSink& diagnostics_;
    Status status_{Status::Available};
    std::uint32_t bad_cycles_{0U};
    std::uint32_t recovery_cycles_{0U};
};

}  // namespace e506::wheel_speed
