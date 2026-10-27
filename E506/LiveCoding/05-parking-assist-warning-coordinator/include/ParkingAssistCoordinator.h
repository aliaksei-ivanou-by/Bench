#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>

namespace e506::parking {

using Milliseconds = std::int64_t;
inline constexpr std::size_t kSensorCount = 4;

struct DistanceSample {
    double distance_m;
    Milliseconds timestamp_ms;
    bool acquisition_valid;
};

enum class Warning {
    Unknown,
    Clear,
    Caution,
    Near,
    Critical
};

enum class Coverage {
    Full,
    Degraded
};

class IDistanceSensorProvider {
public:
    virtual ~IDistanceSensorProvider() = default;
    virtual DistanceSample read(std::size_t sensor_index) = 0;
};

class IMonotonicClock {
public:
    virtual ~IMonotonicClock() = default;
    virtual Milliseconds nowMs() const = 0;
};

class IWarningOutput {
public:
    virtual ~IWarningOutput() = default;
    virtual void publish(Warning warning) = 0;
};

class ICoverageOutput {
public:
    virtual ~ICoverageOutput() = default;
    virtual void publish(Coverage coverage) = 0;
};

class ParkingAssistCoordinator {
public:
    ParkingAssistCoordinator(IDistanceSensorProvider& sensors,
                             const IMonotonicClock& clock,
                             IWarningOutput& warnings,
                             ICoverageOutput& coverage);

    void evaluate();
    Warning warning() const noexcept;
    Coverage coverage() const noexcept;

private:
    void publishIfChanged(Warning next_warning, Coverage next_coverage);

    IDistanceSensorProvider& sensors_;
    const IMonotonicClock& clock_;
    IWarningOutput& warnings_;
    ICoverageOutput& coverage_output_;
    std::array<std::optional<Milliseconds>, kSensorCount>
        last_accepted_timestamps_{};
    std::optional<Warning> last_published_warning_;
    std::optional<Coverage> last_published_coverage_;
    Warning warning_{Warning::Unknown};
    Coverage coverage_{Coverage::Degraded};
};

}  // namespace e506::parking
