#pragma once

#include <cstdint>
#include <optional>

namespace e506::steering {

using Milliseconds = std::int64_t;

struct SteeringCommand {
    double requested_torque_nm;
    Milliseconds timestamp_ms;
    bool driver_override;
};

enum class Diagnostic {
    MissingCommand,
    StaleCommand,
    InvalidCommand,
    InvalidTime,
    ActuatorRejected
};

class ICommandSource {
public:
    virtual ~ICommandSource() = default;
    virtual std::optional<SteeringCommand> read() = 0;
};

class IMonotonicClock {
public:
    virtual ~IMonotonicClock() = default;
    virtual Milliseconds nowMs() const = 0;
};

class ISteeringActuator {
public:
    virtual ~ISteeringActuator() = default;
    virtual bool applyTorque(double torque_nm) = 0;
};

class IDiagnosticSink {
public:
    virtual ~IDiagnosticSink() = default;
    virtual void report(Diagnostic diagnostic) = 0;
};

class SteeringCommandLimiter {
public:
    SteeringCommandLimiter(ICommandSource& source,
                           const IMonotonicClock& clock,
                           ISteeringActuator& actuator,
                           IDiagnosticSink& diagnostics,
                           Milliseconds initial_time_ms = 0);

    void tick();
    double lastAcceptedTorqueNm() const noexcept;
    Milliseconds lastAcceptedTimeMs() const noexcept;

private:
    ICommandSource& source_;
    const IMonotonicClock& clock_;
    ISteeringActuator& actuator_;
    IDiagnosticSink& diagnostics_;
    double last_accepted_torque_nm_{0.0};
    Milliseconds last_accepted_time_ms_;
};

}  // namespace e506::steering
