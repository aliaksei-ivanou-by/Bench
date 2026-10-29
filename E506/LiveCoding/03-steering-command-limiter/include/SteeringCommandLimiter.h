#pragma once

#include <cstdint>
#include <optional>

namespace e506::steering {


struct SteeringCommand {
    double requested_torque_nm;
    std::int64_t timestamp_ms;
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
    virtual std::int64_t nowMs() const = 0;
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
                           std::int64_t initial_time_ms = 0);

    void tick();
    double lastAcceptedTorqueNm() const noexcept;
    std::int64_t lastAcceptedTimeMs() const noexcept;

private:
    ICommandSource& source_;
    const IMonotonicClock& clock_;
    ISteeringActuator& actuator_;
    IDiagnosticSink& diagnostics_;
    double last_accepted_torque_nm_{0.0};
    std::int64_t last_accepted_time_ms_;
};

}  // namespace e506::steering
