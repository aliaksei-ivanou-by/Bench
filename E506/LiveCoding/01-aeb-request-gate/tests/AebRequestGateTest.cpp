#include "AebRequestGate.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>
#include <optional>

namespace e506::aeb {
namespace {


class MockPerceptionSource : public IPerceptionSource {
public:
    MOCK_METHOD(std::optional<PerceptionSample>, read, (), (override));
};

class MockClock : public IMonotonicClock {
public:
    MOCK_METHOD(std::int64_t, nowMs, (), (const, override));
};

class MockBrakeActuator : public IBrakeActuator {
public:
    MOCK_METHOD(bool, requestDeceleration, (double), (override));
};

class MockDiagnosticSink : public IDiagnosticSink {
public:
    MOCK_METHOD(void, report, (Diagnostic), (override));
};

class AebRequestGateTest : public ::testing::Test {
protected:
    PerceptionSample hazardousSample() const {
        return {20.0, 0.95, 0.8, 6.0, 950, false};
    }

    void expectSample(const PerceptionSample& sample, std::int64_t now = 1000) {
        EXPECT_CALL(source_, read()).WillOnce(::testing::Return(sample));
        EXPECT_CALL(clock_, nowMs()).WillOnce(::testing::Return(now));
    }

    ::testing::StrictMock<MockPerceptionSource> source_;
    ::testing::StrictMock<MockClock> clock_;
    ::testing::StrictMock<MockBrakeActuator> actuator_;
    ::testing::StrictMock<MockDiagnosticSink> diagnostics_;
    AebRequestGate gate_{source_, clock_, actuator_, diagnostics_};
};

TEST_F(AebRequestGateTest, HazardousSampleRequestsBraking) {
    expectSample(hazardousSample());
    EXPECT_CALL(actuator_, requestDeceleration(6.0)).WillOnce(::testing::Return(true));
    gate_.tick();
}

TEST_F(AebRequestGateTest, ExactHazardThresholdsAreAccepted) {
    PerceptionSample sample = hazardousSample();
    sample.speed_mps = 5.0;
    sample.confidence = 0.90;
    sample.time_to_collision_s = 1.20;
    sample.timestamp_ms = 900;
    expectSample(sample);
    EXPECT_CALL(actuator_, requestDeceleration(6.0)).WillOnce(::testing::Return(true));
    gate_.tick();
}

TEST_F(AebRequestGateTest, ValuesOutsideHazardThresholdsDoNotRequestBraking) {
    PerceptionSample sample = hazardousSample();
    sample.speed_mps = 4.99;
    expectSample(sample);
    gate_.tick();

    sample = hazardousSample();
    sample.confidence = 0.899;
    expectSample(sample);
    gate_.tick();

    sample = hazardousSample();
    sample.time_to_collision_s = 1.201;
    expectSample(sample);
    gate_.tick();
}

TEST_F(AebRequestGateTest, DriverOverrideSuppressesActuatorInteraction) {
    PerceptionSample sample = hazardousSample();
    sample.driver_override = true;
    expectSample(sample);
    gate_.tick();
}

TEST_F(AebRequestGateTest, MissingSampleReportsDiagnostic) {
    EXPECT_CALL(source_, read()).WillOnce(::testing::Return(std::nullopt));
    EXPECT_CALL(diagnostics_, report(Diagnostic::MissingSample));
    gate_.tick();
}

TEST_F(AebRequestGateTest, SampleAtAgeLimitIsAccepted) {
    PerceptionSample sample = hazardousSample();
    sample.timestamp_ms = 900;
    expectSample(sample);
    EXPECT_CALL(actuator_, requestDeceleration(6.0)).WillOnce(::testing::Return(true));
    gate_.tick();
}

TEST_F(AebRequestGateTest, SamplePastAgeLimitIsRejected) {
    PerceptionSample sample = hazardousSample();
    sample.timestamp_ms = 899;
    expectSample(sample);
    EXPECT_CALL(diagnostics_, report(Diagnostic::StaleSample));
    gate_.tick();
}

TEST_F(AebRequestGateTest, InvalidNumericInputIsRejected) {
    PerceptionSample sample = hazardousSample();
    sample.confidence = std::numeric_limits<double>::quiet_NaN();
    expectSample(sample);
    EXPECT_CALL(diagnostics_, report(Diagnostic::InvalidSample));
    gate_.tick();

    sample = hazardousSample();
    sample.speed_mps = -0.1;
    expectSample(sample);
    EXPECT_CALL(diagnostics_, report(Diagnostic::InvalidSample));
    gate_.tick();

    sample = hazardousSample();
    sample.time_to_collision_s = std::numeric_limits<double>::infinity();
    expectSample(sample);
    EXPECT_CALL(diagnostics_, report(Diagnostic::InvalidSample));
    gate_.tick();
}

TEST_F(AebRequestGateTest, ExcessiveDecelerationIsClamped) {
    PerceptionSample sample = hazardousSample();
    sample.desired_deceleration_mps2 = 12.0;
    expectSample(sample);
    EXPECT_CALL(actuator_, requestDeceleration(8.0)).WillOnce(::testing::Return(true));
    gate_.tick();
}

TEST_F(AebRequestGateTest, ActuatorRejectionIsReported) {
    expectSample(hazardousSample());
    EXPECT_CALL(actuator_, requestDeceleration(6.0)).WillOnce(::testing::Return(false));
    EXPECT_CALL(diagnostics_, report(Diagnostic::ActuatorRejected));
    gate_.tick();
}

TEST_F(AebRequestGateTest, ExtremeTimestampIsStaleWithoutOverflow) {
    PerceptionSample sample = hazardousSample();
    sample.timestamp_ms = std::numeric_limits<std::int64_t>::min();
    expectSample(sample, std::numeric_limits<std::int64_t>::max());
    EXPECT_CALL(diagnostics_, report(Diagnostic::StaleSample));
    gate_.tick();
}

}  // namespace
}  // namespace e506::aeb
