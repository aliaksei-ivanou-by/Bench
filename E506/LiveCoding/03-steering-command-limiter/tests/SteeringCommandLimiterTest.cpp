#include "SteeringCommandLimiter.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>
#include <optional>

namespace e506::steering {
namespace {


class MockCommandSource : public ICommandSource {
public:
    MOCK_METHOD(std::optional<SteeringCommand>, read, (), (override));
};

class MockClock : public IMonotonicClock {
public:
    MOCK_METHOD(std::int64_t, nowMs, (), (const, override));
};

class MockSteeringActuator : public ISteeringActuator {
public:
    MOCK_METHOD(bool, applyTorque, (double), (override));
};

class MockDiagnosticSink : public IDiagnosticSink {
public:
    MOCK_METHOD(void, report, (Diagnostic), (override));
};

class SteeringCommandLimiterTest : public ::testing::Test {
protected:
    void expectCommand(const SteeringCommand& command, std::int64_t now) {
        EXPECT_CALL(source_, read()).WillOnce(::testing::Return(command));
        EXPECT_CALL(clock_, nowMs()).WillOnce(::testing::Return(now));
    }

    ::testing::StrictMock<MockCommandSource> source_;
    ::testing::StrictMock<MockClock> clock_;
    ::testing::StrictMock<MockSteeringActuator> actuator_;
    ::testing::StrictMock<MockDiagnosticSink> diagnostics_;
    SteeringCommandLimiter limiter_{source_, clock_, actuator_, diagnostics_};
};

TEST_F(SteeringCommandLimiterTest, OrdinaryCommandPassesBothLimits) {
    expectCommand({2.0, 100, false}, 100);
    EXPECT_CALL(actuator_, applyTorque(2.0)).WillOnce(::testing::Return(true));
    limiter_.tick();
    EXPECT_DOUBLE_EQ(limiter_.lastAcceptedTorqueNm(), 2.0);
}

TEST_F(SteeringCommandLimiterTest, ExactAbsoluteBoundariesAreAccepted) {
    expectCommand({3.0, 100, false}, 100);
    EXPECT_CALL(actuator_, applyTorque(3.0)).WillOnce(::testing::Return(true));
    limiter_.tick();

    expectCommand({-3.0, 220, false}, 220);
    EXPECT_CALL(actuator_, applyTorque(-3.0)).WillOnce(::testing::Return(true));
    limiter_.tick();
}

TEST_F(SteeringCommandLimiterTest, AbsoluteLimitClampsLargeCommand) {
    expectCommand({10.0, 100, false}, 100);
    EXPECT_CALL(actuator_, applyTorque(3.0)).WillOnce(::testing::Return(true));
    limiter_.tick();
}

TEST_F(SteeringCommandLimiterTest, PositiveAndNegativeRateAreLimited) {
    expectCommand({3.0, 20, false}, 20);
    EXPECT_CALL(actuator_, applyTorque(::testing::DoubleNear(1.0, 1e-12)))
        .WillOnce(::testing::Return(true));
    limiter_.tick();

    expectCommand({-3.0, 40, false}, 40);
    EXPECT_CALL(actuator_, applyTorque(::testing::DoubleNear(0.0, 1e-12)))
        .WillOnce(::testing::Return(true));
    limiter_.tick();
}

TEST_F(SteeringCommandLimiterTest, VariableElapsedTimeChangesAllowedDelta) {
    expectCommand({1.0, 20, false}, 20);
    EXPECT_CALL(actuator_, applyTorque(1.0)).WillOnce(::testing::Return(true));
    limiter_.tick();

    expectCommand({3.0, 50, false}, 50);
    EXPECT_CALL(actuator_, applyTorque(::testing::DoubleNear(2.5, 1e-12)))
        .WillOnce(::testing::Return(true));
    limiter_.tick();
}

TEST_F(SteeringCommandLimiterTest, ZeroElapsedTimeIsRejected) {
    SteeringCommandLimiter limiter(source_, clock_, actuator_, diagnostics_, 100);
    expectCommand({1.0, 100, false}, 100);
    EXPECT_CALL(diagnostics_, report(Diagnostic::InvalidTime));
    limiter.tick();
}

TEST_F(SteeringCommandLimiterTest, NegativeElapsedTimeIsRejected) {
    SteeringCommandLimiter limiter(source_, clock_, actuator_, diagnostics_, 100);
    expectCommand({1.0, 99, false}, 99);
    EXPECT_CALL(diagnostics_, report(Diagnostic::InvalidTime));
    limiter.tick();
}

class InvalidTorqueTest : public SteeringCommandLimiterTest,
                          public ::testing::WithParamInterface<double> {};

TEST_P(InvalidTorqueTest, NonFiniteTorqueIsRejected) {
    expectCommand({GetParam(), 100, false}, 100);
    EXPECT_CALL(diagnostics_, report(Diagnostic::InvalidCommand));
    limiter_.tick();
}

INSTANTIATE_TEST_SUITE_P(
    NonFiniteValues,
    InvalidTorqueTest,
    ::testing::Values(std::numeric_limits<double>::quiet_NaN(),
                      std::numeric_limits<double>::infinity()));

TEST_F(SteeringCommandLimiterTest, FreshnessBoundaryIsInclusive) {
    expectCommand({2.0, 50, false}, 100);
    EXPECT_CALL(actuator_, applyTorque(2.0)).WillOnce(::testing::Return(true));
    limiter_.tick();
}

TEST_F(SteeringCommandLimiterTest, CommandPastFreshnessBoundaryIsRejected) {
    expectCommand({2.0, 49, false}, 100);
    EXPECT_CALL(diagnostics_, report(Diagnostic::StaleCommand));
    limiter_.tick();
}

TEST_F(SteeringCommandLimiterTest, DriverOverrideCommandsImmediateZero) {
    expectCommand({3.0, 20, true}, 20);
    EXPECT_CALL(actuator_, applyTorque(0.0)).WillOnce(::testing::Return(true));
    limiter_.tick();
}

TEST_F(SteeringCommandLimiterTest, ActuatorFailurePreservesAcceptedState) {
    expectCommand({2.0, 100, false}, 100);
    EXPECT_CALL(actuator_, applyTorque(2.0)).WillOnce(::testing::Return(true));
    limiter_.tick();

    expectCommand({3.0, 120, false}, 120);
    EXPECT_CALL(actuator_, applyTorque(3.0)).WillOnce(::testing::Return(false));
    EXPECT_CALL(diagnostics_, report(Diagnostic::ActuatorRejected));
    limiter_.tick();

    EXPECT_DOUBLE_EQ(limiter_.lastAcceptedTorqueNm(), 2.0);
    EXPECT_EQ(limiter_.lastAcceptedTimeMs(), 100);
}

TEST_F(SteeringCommandLimiterTest, ExtremeTimestampIsStaleWithoutOverflow) {
    expectCommand({1.0, std::numeric_limits<std::int64_t>::min(), false}, 100);
    EXPECT_CALL(diagnostics_, report(Diagnostic::StaleCommand));
    limiter_.tick();
}

TEST_F(SteeringCommandLimiterTest, UnrepresentableElapsedTimeIsRejected) {
    const std::int64_t first = std::numeric_limits<std::int64_t>::min();
    const std::int64_t now = std::numeric_limits<std::int64_t>::max();
    SteeringCommandLimiter limiter(source_, clock_, actuator_, diagnostics_, first);
    expectCommand({1.0, now, false}, now);
    EXPECT_CALL(diagnostics_, report(Diagnostic::InvalidTime));
    limiter.tick();
    EXPECT_EQ(limiter.lastAcceptedTimeMs(), first);
}

}  // namespace
}  // namespace e506::steering
