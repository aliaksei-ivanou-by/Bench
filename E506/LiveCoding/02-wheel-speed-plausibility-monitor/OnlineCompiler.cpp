// Самостоятельная копия заголовка, эталонной реализации и тестов.


#include <cstdint>
#include <optional>

namespace e506::wheel_speed {


struct SpeedSample {
    double speed_mps;
    std::int64_t timestamp_ms;
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
    virtual std::int64_t nowMs() const = 0;
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
    std::uint32_t bad_cycles_{0U};
    std::uint32_t recovery_cycles_{0U};
};

}  // namespace e506::wheel_speed


#include <cmath>

namespace e506::wheel_speed {
namespace {

constexpr double kMinimumSpeedMps = 0.0;
constexpr double kMaximumSpeedMps = 100.0;
constexpr double kMaximumDifferenceMps = 1.5;
constexpr std::int64_t kMaximumSampleAgeMs = 50;
constexpr std::uint32_t kBadCyclesBeforeDegraded = 3U;
constexpr std::uint32_t kGoodCyclesBeforeRecovery = 5U;

// Предусловие: timestamp_ms <= now_ms, а max_age_ms неотрицателен.
bool isStale(std::int64_t now_ms, std::int64_t timestamp_ms,
             std::int64_t max_age_ms) noexcept {
    return (timestamp_ms >= 0) ? ((now_ms - timestamp_ms) > max_age_ms)
                               : (now_ms > (timestamp_ms + max_age_ms));
}

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
    const std::optional<SpeedSample> primary = primary_.read();
    const std::optional<SpeedSample> secondary = secondary_.read();
    if (!primary || !secondary) {
        degradeImmediately(Diagnostic::MissingSample);
        return;
    }

    const std::int64_t now_ms = clock_.nowMs();
    if (primary->timestamp_ms > now_ms || secondary->timestamp_ms > now_ms) {
        degradeImmediately(Diagnostic::InvalidSample);
        return;
    }
    if (isStale(now_ms, primary->timestamp_ms, kMaximumSampleAgeMs) ||
        isStale(now_ms, secondary->timestamp_ms, kMaximumSampleAgeMs)) {
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
        recovery_cycles_ = 0U;
        if (plausible) {
            bad_cycles_ = 0U;
            return;
        }
        ++bad_cycles_;
        if (bad_cycles_ >= kBadCyclesBeforeDegraded) {
            bad_cycles_ = 0U;
            enter(Status::Degraded);
        }
        return;
    }

    bad_cycles_ = 0U;
    if (!plausible) {
        recovery_cycles_ = 0U;
        return;
    }
    ++recovery_cycles_;
    if (recovery_cycles_ >= kGoodCyclesBeforeRecovery) {
        recovery_cycles_ = 0U;
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
    bad_cycles_ = 0U;
    recovery_cycles_ = 0U;
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

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
