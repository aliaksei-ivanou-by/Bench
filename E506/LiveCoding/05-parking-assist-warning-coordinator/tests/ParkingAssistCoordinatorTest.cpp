#include "ParkingAssistCoordinator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <array>
#include <limits>
#include <tuple>

namespace e506::parking {
namespace {


class MockSensorProvider : public IDistanceSensorProvider {
public:
    MOCK_METHOD(DistanceSample, read, (std::size_t), (override));
};

class MockClock : public IMonotonicClock {
public:
    MOCK_METHOD(std::int64_t, nowMs, (), (const, override));
};

class MockWarningOutput : public IWarningOutput {
public:
    MOCK_METHOD(void, publish, (Warning), (override));
};

class MockCoverageOutput : public ICoverageOutput {
public:
    MOCK_METHOD(void, publish, (Coverage), (override));
};

class ParkingAssistCoordinatorTest : public ::testing::Test {
protected:
    DistanceSample sample(double distance,
                          std::int64_t timestamp = 900,
                          bool valid = true) const {
        return {distance, timestamp, valid};
    }

    void expectCycle(const std::array<DistanceSample, kSensorCount>& samples,
                     std::int64_t now = 1000) {
        EXPECT_CALL(clock_, nowMs()).WillOnce(::testing::Return(now));
        for (std::size_t index = 0U; index < kSensorCount; ++index) {
            EXPECT_CALL(sensors_, read(index)).WillOnce(::testing::Return(samples[index]));
        }
    }

    std::array<DistanceSample, kSensorCount> clearSamples() const {
        return {sample(2.0), sample(2.5), sample(3.0), sample(4.0)};
    }

    ::testing::StrictMock<MockSensorProvider> sensors_;
    ::testing::StrictMock<MockClock> clock_;
    ::testing::StrictMock<MockWarningOutput> warnings_;
    ::testing::StrictMock<MockCoverageOutput> coverage_;
    ParkingAssistCoordinator coordinator_{sensors_, clock_, warnings_, coverage_};
};

TEST_F(ParkingAssistCoordinatorTest, FourClearSamplesPublishClearAndFull) {
    expectCycle(clearSamples());
    EXPECT_CALL(warnings_, publish(Warning::Clear));
    EXPECT_CALL(coverage_, publish(Coverage::Full));
    coordinator_.evaluate();
}

TEST_F(ParkingAssistCoordinatorTest, NearestSampleWinsRegardlessOfIndex) {
    std::array<DistanceSample, kSensorCount> samples = clearSamples();
    samples[2] = sample(0.25);
    expectCycle(samples);
    EXPECT_CALL(warnings_, publish(Warning::Critical));
    EXPECT_CALL(coverage_, publish(Coverage::Full));
    coordinator_.evaluate();
}

class WarningBoundaryTest
    : public ParkingAssistCoordinatorTest,
      public ::testing::WithParamInterface<std::tuple<double, Warning>> {};

TEST_P(WarningBoundaryTest, DistanceMapsToExpectedWarning) {
    std::array<DistanceSample, kSensorCount> samples = clearSamples();
    samples[0] = sample(std::get<0>(GetParam()));
    expectCycle(samples);
    EXPECT_CALL(warnings_, publish(std::get<1>(GetParam())));
    EXPECT_CALL(coverage_, publish(Coverage::Full));
    coordinator_.evaluate();
}

INSTANTIATE_TEST_SUITE_P(
    Boundaries,
    WarningBoundaryTest,
    ::testing::Values(std::make_tuple(0.30, Warning::Critical),
                      std::make_tuple(0.3001, Warning::Near),
                      std::make_tuple(0.80, Warning::Near),
                      std::make_tuple(0.8001, Warning::Caution),
                      std::make_tuple(1.50, Warning::Caution),
                      std::make_tuple(1.5001, Warning::Clear)));

TEST_F(ParkingAssistCoordinatorTest, PhysicalRangeBoundariesAreUsable) {
    std::array<DistanceSample, kSensorCount> samples = clearSamples();
    samples[0] = sample(0.10);
    samples[1] = sample(5.00);
    expectCycle(samples);
    EXPECT_CALL(warnings_, publish(Warning::Critical));
    EXPECT_CALL(coverage_, publish(Coverage::Full));
    coordinator_.evaluate();
}

TEST_F(ParkingAssistCoordinatorTest, SampleAtFreshnessBoundaryIsUsable) {
    std::array<DistanceSample, kSensorCount> samples = clearSamples();
    samples[0] = sample(0.25, 800);
    expectCycle(samples);
    EXPECT_CALL(warnings_, publish(Warning::Critical));
    EXPECT_CALL(coverage_, publish(Coverage::Full));
    coordinator_.evaluate();
}

TEST_F(ParkingAssistCoordinatorTest, ExtremeTimestampsAreStaleWithoutOverflow) {
    std::array<DistanceSample, kSensorCount> samples = clearSamples();
    for (DistanceSample& reading : samples) {
        reading.timestamp_ms = std::numeric_limits<std::int64_t>::min();
    }
    expectCycle(samples, std::numeric_limits<std::int64_t>::max());
    EXPECT_CALL(warnings_, publish(Warning::Unknown));
    EXPECT_CALL(coverage_, publish(Coverage::Degraded));
    coordinator_.evaluate();
}

TEST_F(ParkingAssistCoordinatorTest, OneInvalidSensorKeepsWarningAndDegradesCoverage) {
    std::array<DistanceSample, kSensorCount> samples = clearSamples();
    samples[0] = sample(0.05);
    expectCycle(samples);
    EXPECT_CALL(warnings_, publish(Warning::Clear));
    EXPECT_CALL(coverage_, publish(Coverage::Degraded));
    coordinator_.evaluate();
}

TEST_F(ParkingAssistCoordinatorTest, AllInvalidSensorsPublishUnknownNotClear) {
    std::array<DistanceSample, kSensorCount> samples = clearSamples();
    for (DistanceSample& value : samples) {
        value.acquisition_valid = false;
    }
    expectCycle(samples);
    EXPECT_CALL(warnings_, publish(Warning::Unknown));
    EXPECT_CALL(coverage_, publish(Coverage::Degraded));
    coordinator_.evaluate();
}

TEST_F(ParkingAssistCoordinatorTest, OutOfOrderSampleIsRejectedWithoutCorruptingTimestamp) {
    expectCycle(clearSamples());
    EXPECT_CALL(warnings_, publish(Warning::Clear));
    EXPECT_CALL(coverage_, publish(Coverage::Full));
    coordinator_.evaluate();

    std::array<DistanceSample, kSensorCount> older = clearSamples();
    older[0] = sample(0.20, 899);
    expectCycle(older);
    EXPECT_CALL(coverage_, publish(Coverage::Degraded));
    coordinator_.evaluate();

    std::array<DistanceSample, kSensorCount> recovered = clearSamples();
    recovered[0] = sample(2.0, 901);
    expectCycle(recovered);
    EXPECT_CALL(coverage_, publish(Coverage::Full));
    coordinator_.evaluate();
}

TEST_F(ParkingAssistCoordinatorTest, RepeatedStateProducesNoExtraOutputs) {
    expectCycle(clearSamples());
    EXPECT_CALL(warnings_, publish(Warning::Clear));
    EXPECT_CALL(coverage_, publish(Coverage::Full));
    coordinator_.evaluate();

    expectCycle(clearSamples());
    coordinator_.evaluate();
}

TEST_F(ParkingAssistCoordinatorTest, SensorRecoveryRestoresFullCoverage) {
    std::array<DistanceSample, kSensorCount> degraded = clearSamples();
    degraded[0].acquisition_valid = false;
    expectCycle(degraded);
    EXPECT_CALL(warnings_, publish(Warning::Clear));
    EXPECT_CALL(coverage_, publish(Coverage::Degraded));
    coordinator_.evaluate();

    expectCycle(clearSamples());
    EXPECT_CALL(coverage_, publish(Coverage::Full));
    coordinator_.evaluate();
}

}  // namespace
}  // namespace e506::parking
