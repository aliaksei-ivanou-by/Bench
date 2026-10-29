#include "WheelSpeedMonitor.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>
#include <optional>

namespace e506::wheel_speed {
namespace {


class MockSensor : public ISpeedSensor {
public:
    MOCK_METHOD(std::optional<SpeedSample>, read, (), (override));
};

class MockClock : public IMonotonicClock {
public:
    MOCK_METHOD(std::int64_t, nowMs, (), (const, override));
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
                     std::int64_t now = 1000) {
        EXPECT_CALL(primary_, read()).WillOnce(::testing::Return(primary));
        EXPECT_CALL(secondary_, read()).WillOnce(::testing::Return(secondary));
        if (primary && secondary) {
            EXPECT_CALL(clock_, nowMs()).WillOnce(::testing::Return(now));
        }
    }

    SpeedSample sample(double value, std::int64_t timestamp = 980) const {
        return {value, timestamp};
    }

    ::testing::StrictMock<MockSensor> primary_;
    ::testing::StrictMock<MockSensor> secondary_;
    ::testing::StrictMock<MockClock> clock_;
    ::testing::StrictMock<MockStatusOutput> output_;
    ::testing::StrictMock<MockDiagnosticSink> diagnostics_;
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

TEST_F(WheelSpeedMonitorTest, ExtremeTimestampIsStaleWithoutOverflow) {
    const std::int64_t now = std::numeric_limits<std::int64_t>::max();
    expectCycle(sample(20.0, std::numeric_limits<std::int64_t>::min()),
                sample(20.0, now), now);
    EXPECT_CALL(diagnostics_, report(Diagnostic::StaleSample));
    EXPECT_CALL(output_, publish(Status::Degraded));
    monitor_.tick();
}

TEST_F(WheelSpeedMonitorTest, NegativeTimestampAgeBoundaryIsInclusive) {
    expectCycle(sample(20.0, -50), sample(20.0, -50), 0);
    monitor_.tick();
    EXPECT_EQ(monitor_.status(), Status::Available);
}

}  // namespace
}  // namespace e506::wheel_speed
