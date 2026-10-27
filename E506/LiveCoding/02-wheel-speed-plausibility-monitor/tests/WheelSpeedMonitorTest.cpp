#include "WheelSpeedMonitor.h"

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
