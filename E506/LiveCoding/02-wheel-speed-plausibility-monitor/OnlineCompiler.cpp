// Standalone copy of the header, reference implementation and tests.


#include <cstdint>
#include <optional>

namespace e506::wheel_speed {

using Milliseconds = std::int64_t;

struct SpeedSample {
    double speed_mps;
    Milliseconds timestamp_ms;
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
    virtual Milliseconds nowMs() const = 0;
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
    unsigned bad_cycles_{0};
    unsigned recovery_cycles_{0};
};

}  // namespace e506::wheel_speed


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


#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>
#include <optional>

namespace e506::wheel_speed {
namespace {

using ::testing::Return;
using ::testing::StrictMock;

class MockSensor : public ISpeedSensor {
public:
    MOCK_METHOD(std::optional<SpeedSample>, read, (), (override));
};

class MockClock : public IMonotonicClock {
public:
    MOCK_METHOD(Milliseconds, nowMs, (), (const, override));
};

class MockStatusOutput : public IStatusOutput {
public:
    MOCK_METHOD(void, publish, (Status), (override));
};

class MockDiagnosticSink : public IDiagnosticSink {
public:
    MOCK_METHOD(void, report, (Diagnostic), (override));
};

class WheelSpeedMonitorTest : public ::testing::Test {
protected:
    void expectCycle(std::optional<SpeedSample> primary,
                     std::optional<SpeedSample> secondary,
                     Milliseconds now = 1000) {
        EXPECT_CALL(primary_, read()).WillOnce(Return(primary));
        EXPECT_CALL(secondary_, read()).WillOnce(Return(secondary));
        if (primary && secondary) {
            EXPECT_CALL(clock_, nowMs()).WillOnce(Return(now));
        }
    }

    SpeedSample sample(double value, Milliseconds timestamp = 980) const {
        return {value, timestamp};
    }

    StrictMock<MockSensor> primary_;
    StrictMock<MockSensor> secondary_;
    StrictMock<MockClock> clock_;
    StrictMock<MockStatusOutput> output_;
    StrictMock<MockDiagnosticSink> diagnostics_;
    WheelSpeedMonitor monitor_{primary_, secondary_, clock_, output_, diagnostics_};
};

TEST_F(WheelSpeedMonitorTest, EqualValuesKeepAvailableWithoutNotification) {
    expectCycle(sample(20.0), sample(20.0));
    monitor_.tick();
    EXPECT_EQ(monitor_.status(), Status::Available);
}

TEST_F(WheelSpeedMonitorTest, ExactDifferenceLimitIsPlausible) {
    expectCycle(sample(20.0), sample(21.5));
    monitor_.tick();
    EXPECT_EQ(monitor_.status(), Status::Available);
}

TEST_F(WheelSpeedMonitorTest, ThirdConsecutiveBadCycleDegrades) {
    for (int cycle = 0; cycle < 2; ++cycle) {
        expectCycle(sample(20.0), sample(21.6));
        monitor_.tick();
    }
    expectCycle(sample(20.0), sample(21.6));
    EXPECT_CALL(output_, publish(Status::Degraded));
    monitor_.tick();
    EXPECT_EQ(monitor_.status(), Status::Degraded);
}

TEST_F(WheelSpeedMonitorTest, PlausibleCycleResetsBadCounter) {
    for (int cycle = 0; cycle < 2; ++cycle) {
        expectCycle(sample(20.0), sample(21.6));
        monitor_.tick();
    }
    expectCycle(sample(20.0), sample(20.5));
    monitor_.tick();
    for (int cycle = 0; cycle < 2; ++cycle) {
        expectCycle(sample(20.0), sample(21.6));
        monitor_.tick();
    }
    EXPECT_EQ(monitor_.status(), Status::Available);
}

TEST_F(WheelSpeedMonitorTest, MissingSensorDegradesImmediately) {
    expectCycle(std::nullopt, sample(20.0));
    EXPECT_CALL(diagnostics_, report(Diagnostic::MissingSample));
    EXPECT_CALL(output_, publish(Status::Degraded));
    monitor_.tick();
}

TEST_F(WheelSpeedMonitorTest, FiftyMillisecondSampleIsAccepted) {
    expectCycle(sample(20.0, 950), sample(20.5, 950));
    monitor_.tick();
    EXPECT_EQ(monitor_.status(), Status::Available);
}

TEST_F(WheelSpeedMonitorTest, FiftyOneMillisecondSampleIsStale) {
    expectCycle(sample(20.0, 949), sample(20.5, 950));
    EXPECT_CALL(diagnostics_, report(Diagnostic::StaleSample));
    EXPECT_CALL(output_, publish(Status::Degraded));
    monitor_.tick();
}

class InvalidWheelValueTest : public WheelSpeedMonitorTest,
                              public ::testing::WithParamInterface<double> {};

TEST_P(InvalidWheelValueTest, InvalidValueDegradesImmediately) {
    expectCycle(sample(GetParam()), sample(20.0));
    EXPECT_CALL(diagnostics_, report(Diagnostic::InvalidSample));
    EXPECT_CALL(output_, publish(Status::Degraded));
    monitor_.tick();
}

INSTANTIATE_TEST_SUITE_P(
    InvalidValues,
    InvalidWheelValueTest,
    ::testing::Values(std::numeric_limits<double>::quiet_NaN(),
                      std::numeric_limits<double>::infinity(),
                      -0.1,
                      100.1));

TEST_F(WheelSpeedMonitorTest, FifthPlausibleCycleRecovers) {
    expectCycle(std::nullopt, sample(20.0));
    EXPECT_CALL(diagnostics_, report(Diagnostic::MissingSample));
    EXPECT_CALL(output_, publish(Status::Degraded));
    monitor_.tick();

    for (int cycle = 0; cycle < 4; ++cycle) {
        expectCycle(sample(20.0), sample(20.5));
        monitor_.tick();
        EXPECT_EQ(monitor_.status(), Status::Degraded);
    }
    expectCycle(sample(20.0), sample(20.5));
    EXPECT_CALL(output_, publish(Status::Available));
    monitor_.tick();
    EXPECT_EQ(monitor_.status(), Status::Available);
}

TEST_F(WheelSpeedMonitorTest, RepeatedDegradedCyclesDoNotRepublishStatus) {
    expectCycle(std::nullopt, sample(20.0));
    EXPECT_CALL(diagnostics_, report(Diagnostic::MissingSample));
    EXPECT_CALL(output_, publish(Status::Degraded));
    monitor_.tick();

    expectCycle(std::nullopt, sample(20.0));
    EXPECT_CALL(diagnostics_, report(Diagnostic::MissingSample));
    monitor_.tick();
}

}  // namespace
}  // namespace e506::wheel_speed

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
