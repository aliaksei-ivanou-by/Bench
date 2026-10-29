#include "BatteryThermalSupervisor.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>

namespace e506::battery {
namespace {


class MockTemperatureSensor : public ITemperatureSensor {
public:
    MOCK_METHOD(TemperatureSample, read, (), (override));
};

class MockClock : public IMonotonicClock {
public:
    MOCK_METHOD(std::int64_t, nowMs, (), (const, override));
};

class MockCoolingControl : public ICoolingControl {
public:
    MOCK_METHOD(void, setEnabled, (bool), (override));
};

class MockShutdownControl : public IShutdownControl {
public:
    MOCK_METHOD(void, setRequested, (bool), (override));
};

class MockDiagnosticSink : public IDiagnosticSink {
public:
    MOCK_METHOD(void, report, (Diagnostic), (override));
};

class BatteryThermalSupervisorTest : public ::testing::Test {
protected:
    TemperatureSample sample(double value,
                             std::int64_t timestamp = 900,
                             bool valid = true) const {
        return {value, timestamp, valid};
    }

    void expectSamples(const TemperatureSample& first,
                       const TemperatureSample& second,
                       std::int64_t now = 1000) {
        EXPECT_CALL(first_sensor_, read()).WillOnce(::testing::Return(first));
        EXPECT_CALL(second_sensor_, read()).WillOnce(::testing::Return(second));
        EXPECT_CALL(clock_, nowMs()).WillOnce(::testing::Return(now));
    }

    ::testing::StrictMock<MockTemperatureSensor> first_sensor_;
    ::testing::StrictMock<MockTemperatureSensor> second_sensor_;
    ::testing::StrictMock<MockClock> clock_;
    ::testing::StrictMock<MockCoolingControl> cooling_;
    ::testing::StrictMock<MockShutdownControl> shutdown_;
    ::testing::StrictMock<MockDiagnosticSink> diagnostics_;
    BatteryThermalSupervisor supervisor_{
        first_sensor_, second_sensor_, clock_, cooling_, shutdown_, diagnostics_};
};

TEST_F(BatteryThermalSupervisorTest, CoolPlausiblePairKeepsNormalState) {
    expectSamples(sample(40.0), sample(42.0));
    supervisor_.evaluate();
    EXPECT_EQ(supervisor_.state(), State::Normal);
}

TEST_F(BatteryThermalSupervisorTest, CoolingUsesEnterAndExitHysteresis) {
    expectSamples(sample(55.0), sample(54.0));
    EXPECT_CALL(cooling_, setEnabled(true));
    supervisor_.evaluate();

    expectSamples(sample(52.0), sample(51.0));
    supervisor_.evaluate();
    EXPECT_EQ(supervisor_.state(), State::CoolingRequested);

    expectSamples(sample(50.0), sample(49.0));
    EXPECT_CALL(cooling_, setEnabled(false));
    supervisor_.evaluate();
    EXPECT_EQ(supervisor_.state(), State::Normal);
}

TEST_F(BatteryThermalSupervisorTest, ShutdownThresholdIsInclusive) {
    expectSamples(sample(70.0), sample(69.0));
    EXPECT_CALL(shutdown_, setRequested(true));
    supervisor_.evaluate();
    EXPECT_EQ(supervisor_.state(), State::ShutdownRequested);
}

TEST_F(BatteryThermalSupervisorTest, SingleUsableSensorReportsDegradedSensing) {
    expectSamples(sample(40.0, 900, false), sample(45.0));
    EXPECT_CALL(diagnostics_, report(Diagnostic::DegradedSensing));
    supervisor_.evaluate();
    EXPECT_EQ(supervisor_.state(), State::Normal);
}

TEST_F(BatteryThermalSupervisorTest, SampleAtFreshnessLimitIsUsable) {
    expectSamples(sample(40.0, 750), sample(42.0, 750));
    supervisor_.evaluate();
    EXPECT_EQ(supervisor_.state(), State::Normal);
}

TEST_F(BatteryThermalSupervisorTest, TwoStaleSamplesRequestShutdown) {
    expectSamples(sample(40.0, 749), sample(42.0, 749));
    EXPECT_CALL(diagnostics_, report(Diagnostic::SensorFault));
    EXPECT_CALL(shutdown_, setRequested(true));
    supervisor_.evaluate();
}

TEST_F(BatteryThermalSupervisorTest, ExtremeTimestampsAreStaleWithoutOverflow) {
    const std::int64_t oldest = std::numeric_limits<std::int64_t>::min();
    const std::int64_t now = std::numeric_limits<std::int64_t>::max();
    expectSamples(sample(40.0, oldest), sample(42.0, oldest), now);
    EXPECT_CALL(diagnostics_, report(Diagnostic::SensorFault));
    EXPECT_CALL(shutdown_, setRequested(true));
    supervisor_.evaluate();
    EXPECT_EQ(supervisor_.state(), State::ShutdownRequested);
}

TEST_F(BatteryThermalSupervisorTest, FiveDegreeDisagreementIsAccepted) {
    expectSamples(sample(40.0), sample(45.0));
    supervisor_.evaluate();
    EXPECT_EQ(supervisor_.state(), State::Normal);
}

TEST_F(BatteryThermalSupervisorTest, LargerDisagreementRequestsShutdown) {
    expectSamples(sample(40.0), sample(45.1));
    EXPECT_CALL(diagnostics_, report(Diagnostic::SensorFault));
    EXPECT_CALL(shutdown_, setRequested(true));
    supervisor_.evaluate();
}

TEST_F(BatteryThermalSupervisorTest, LatchedShutdownIgnoresNormalEvaluation) {
    expectSamples(sample(70.0), sample(69.0));
    EXPECT_CALL(shutdown_, setRequested(true));
    supervisor_.evaluate();

    supervisor_.evaluate();
    EXPECT_EQ(supervisor_.state(), State::ShutdownRequested);
}

TEST_F(BatteryThermalSupervisorTest, ResetIsRejectedAboveSafeTemperature) {
    expectSamples(sample(70.0), sample(69.0));
    EXPECT_CALL(shutdown_, setRequested(true));
    supervisor_.evaluate();

    expectSamples(sample(51.0), sample(50.0));
    EXPECT_CALL(diagnostics_, report(Diagnostic::ResetRejected));
    EXPECT_FALSE(supervisor_.reset());
    EXPECT_EQ(supervisor_.state(), State::ShutdownRequested);
}

TEST_F(BatteryThermalSupervisorTest, ValidResetClearsShutdownLatch) {
    expectSamples(sample(70.0), sample(69.0));
    EXPECT_CALL(shutdown_, setRequested(true));
    supervisor_.evaluate();

    expectSamples(sample(50.0), sample(49.0));
    EXPECT_CALL(shutdown_, setRequested(false));
    EXPECT_TRUE(supervisor_.reset());
    EXPECT_EQ(supervisor_.state(), State::Normal);
}

TEST_F(BatteryThermalSupervisorTest, RepeatedCoolingStateDoesNotRepeatOutput) {
    expectSamples(sample(55.0), sample(54.0));
    EXPECT_CALL(cooling_, setEnabled(true));
    supervisor_.evaluate();

    expectSamples(sample(56.0), sample(55.0));
    supervisor_.evaluate();
}

}  // namespace
}  // namespace e506::battery
