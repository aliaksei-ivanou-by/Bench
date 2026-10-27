#include "AmbientLightController.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>

namespace e506::ambient_light {
namespace {

using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

class MockLightDriver : public ILightDriver {
public:
    MOCK_METHOD(bool, apply, (Color), (override));
};

class MockPreferenceStore : public IPreferenceStore {
public:
    MOCK_METHOD(std::optional<Color>, load, (), (override));
    MOCK_METHOD(bool, save, (Color), (override));
};

class MockDiagnosticSink : public IDiagnosticSink {
public:
    MOCK_METHOD(void, report, (Diagnostic), (override));
    MOCK_METHOD(void, clear, (Diagnostic), (override));
};

class AmbientLightControllerTest : public ::testing::Test {
protected:
    void initializeWith(Color color) {
        EXPECT_CALL(preferences_, load()).WillOnce(Return(color));
        EXPECT_CALL(driver_, apply(color)).WillOnce(Return(true));
        EXPECT_TRUE(controller_.initialize());
    }

    StrictMock<MockLightDriver> driver_;
    StrictMock<MockPreferenceStore> preferences_;
    StrictMock<MockDiagnosticSink> diagnostics_;
    AmbientLightController controller_{driver_, preferences_, diagnostics_};
};

TEST_F(AmbientLightControllerTest, SupportedPreferenceIsAppliedAtStartup) {
    EXPECT_CALL(preferences_, load()).WillOnce(Return(Color::Blue));
    EXPECT_CALL(driver_, apply(Color::Blue)).WillOnce(Return(true));
    EXPECT_TRUE(controller_.initialize());
    EXPECT_EQ(controller_.activeColor(), Color::Blue);
}

TEST_F(AmbientLightControllerTest, MissingPreferenceAppliesThenSavesDefault) {
    InSequence sequence;
    EXPECT_CALL(preferences_, load()).WillOnce(Return(std::nullopt));
    EXPECT_CALL(driver_, apply(Color::WarmWhite)).WillOnce(Return(true));
    EXPECT_CALL(preferences_, save(Color::WarmWhite)).WillOnce(Return(true));
    EXPECT_TRUE(controller_.initialize());
    EXPECT_EQ(controller_.activeColor(), Color::WarmWhite);
}

TEST_F(AmbientLightControllerTest, UnsupportedStoredValueIsReplacedByDefault) {
    const auto invalid = static_cast<Color>(99);
    EXPECT_CALL(preferences_, load()).WillOnce(Return(invalid));
    EXPECT_CALL(diagnostics_, report(Diagnostic::UnsupportedValue));
    EXPECT_CALL(driver_, apply(Color::WarmWhite)).WillOnce(Return(true));
    EXPECT_CALL(preferences_, save(Color::WarmWhite)).WillOnce(Return(true));
    EXPECT_TRUE(controller_.initialize());
}

TEST_F(AmbientLightControllerTest, RuntimeChangeAppliesBeforeSaving) {
    initializeWith(Color::Blue);
    InSequence sequence;
    EXPECT_CALL(driver_, apply(Color::Red)).WillOnce(Return(true));
    EXPECT_CALL(preferences_, save(Color::Red)).WillOnce(Return(true));
    EXPECT_TRUE(controller_.setColor(Color::Red));
    EXPECT_EQ(controller_.activeColor(), Color::Red);
}

TEST_F(AmbientLightControllerTest, DriverFailurePreservesActiveStateAndSkipsSave) {
    initializeWith(Color::Blue);
    EXPECT_CALL(driver_, apply(Color::Red)).WillOnce(Return(false));
    EXPECT_CALL(diagnostics_, report(Diagnostic::DriverFailure));
    EXPECT_FALSE(controller_.setColor(Color::Red));
    EXPECT_EQ(controller_.activeColor(), Color::Blue);
}

TEST_F(AmbientLightControllerTest, PersistenceFailureKeepsAppliedColor) {
    initializeWith(Color::Blue);
    EXPECT_CALL(driver_, apply(Color::Red)).WillOnce(Return(true));
    EXPECT_CALL(preferences_, save(Color::Red)).WillOnce(Return(false));
    EXPECT_CALL(diagnostics_, report(Diagnostic::PersistenceFailure));
    EXPECT_FALSE(controller_.setColor(Color::Red));
    EXPECT_EQ(controller_.activeColor(), Color::Red);
}

TEST_F(AmbientLightControllerTest, RepeatedActiveColorHasNoSideEffects) {
    initializeWith(Color::Blue);
    EXPECT_TRUE(controller_.setColor(Color::Blue));
}

TEST_F(AmbientLightControllerTest, UnsupportedRuntimeValueIsRejected) {
    initializeWith(Color::Blue);
    EXPECT_CALL(diagnostics_, report(Diagnostic::UnsupportedValue));
    EXPECT_FALSE(controller_.setColor(static_cast<Color>(99)));
    EXPECT_EQ(controller_.activeColor(), Color::Blue);
}

TEST_F(AmbientLightControllerTest, LaterSuccessfulSaveClearsPersistenceFailure) {
    initializeWith(Color::Blue);

    EXPECT_CALL(driver_, apply(Color::Red)).WillOnce(Return(true));
    EXPECT_CALL(preferences_, save(Color::Red)).WillOnce(Return(false));
    EXPECT_CALL(diagnostics_, report(Diagnostic::PersistenceFailure));
    EXPECT_FALSE(controller_.setColor(Color::Red));

    EXPECT_CALL(driver_, apply(Color::White)).WillOnce(Return(true));
    EXPECT_CALL(preferences_, save(Color::White)).WillOnce(Return(true));
    EXPECT_CALL(diagnostics_, clear(Diagnostic::PersistenceFailure));
    EXPECT_TRUE(controller_.setColor(Color::White));
}

TEST_F(AmbientLightControllerTest, LaterDriverSuccessClearsDriverFailure) {
    initializeWith(Color::Blue);

    EXPECT_CALL(driver_, apply(Color::Red)).WillOnce(Return(false));
    EXPECT_CALL(diagnostics_, report(Diagnostic::DriverFailure));
    EXPECT_FALSE(controller_.setColor(Color::Red));

    EXPECT_CALL(driver_, apply(Color::White)).WillOnce(Return(true));
    EXPECT_CALL(diagnostics_, clear(Diagnostic::DriverFailure));
    EXPECT_CALL(preferences_, save(Color::White)).WillOnce(Return(true));
    EXPECT_TRUE(controller_.setColor(Color::White));
}

}  // namespace
}  // namespace e506::ambient_light
