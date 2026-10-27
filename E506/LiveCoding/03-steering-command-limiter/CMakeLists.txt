cmake_minimum_required(VERSION 3.20)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(SteeringCommandLimiterExercise LANGUAGES CXX)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif()

set(STEERING_LIMITER_IMPLEMENTATION
    "${CMAKE_CURRENT_SOURCE_DIR}/solution/SteeringCommandLimiter.cpp"
    CACHE FILEPATH "Steering limiter implementation compiled by the exercise")

add_library(e506_steering_command_limiter STATIC ${STEERING_LIMITER_IMPLEMENTATION})
target_include_directories(e506_steering_command_limiter PUBLIC include)
target_compile_features(e506_steering_command_limiter PUBLIC cxx_std_17)

add_executable(e506_steering_command_limiter_tests
    tests/SteeringCommandLimiterTest.cpp)
target_link_libraries(e506_steering_command_limiter_tests
    PRIVATE e506_steering_command_limiter GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(e506_steering_command_limiter_tests)
