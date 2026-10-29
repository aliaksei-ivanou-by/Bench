#pragma once

#include <cstdint>
#include <optional>

namespace e506::aeb {


struct PerceptionSample {
    double speed_mps;
    double confidence;
    double time_to_collision_s;
    double desired_deceleration_mps2;
    std::int64_t timestamp_ms;
    bool driver_override;
};

enum class Diagnostic {
    MissingSample,
    StaleSample,
    InvalidSample,
    ActuatorRejected
};

class IPerceptionSource {
public:
    virtual ~IPerceptionSource() = default;
    virtual std::optional<PerceptionSample> read() = 0;
};

class IMonotonicClock {
public:
    virtual ~IMonotonicClock() = default;
    virtual std::int64_t nowMs() const = 0;
};

class IBrakeActuator {
public:
    virtual ~IBrakeActuator() = default;
    virtual bool requestDeceleration(double deceleration_mps2) = 0;
};

class IDiagnosticSink {
public:
    virtual ~IDiagnosticSink() = default;
    virtual void report(Diagnostic diagnostic) = 0;
};

class AebRequestGate {
public:
    AebRequestGate(IPerceptionSource& source,
                   const IMonotonicClock& clock,
                   IBrakeActuator& actuator,
                   IDiagnosticSink& diagnostics);

    void tick();

private:
    IPerceptionSource& source_;
    const IMonotonicClock& clock_;
    IBrakeActuator& actuator_;
    IDiagnosticSink& diagnostics_;
};

}  // namespace e506::aeb
