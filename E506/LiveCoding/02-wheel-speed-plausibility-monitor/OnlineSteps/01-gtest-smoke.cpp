#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Environment, TestFrameworkRuns) { EXPECT_EQ(1 + 1, 2); }

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
