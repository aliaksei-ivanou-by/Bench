cmake_minimum_required(VERSION 3.20)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(WheelSpeedMonitorExercise LANGUAGES CXX)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif()

set(WHEEL_SPEED_IMPLEMENTATION
    "${CMAKE_CURRENT_SOURCE_DIR}/solution/WheelSpeedMonitor.cpp"
    CACHE FILEPATH "Wheel-speed monitor implementation compiled by the exercise")

add_library(e506_wheel_speed_monitor STATIC ${WHEEL_SPEED_IMPLEMENTATION})
target_include_directories(e506_wheel_speed_monitor PUBLIC include)
target_compile_features(e506_wheel_speed_monitor PUBLIC cxx_std_17)

add_executable(e506_wheel_speed_monitor_tests tests/WheelSpeedMonitorTest.cpp)
target_link_libraries(e506_wheel_speed_monitor_tests
    PRIVATE e506_wheel_speed_monitor GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(e506_wheel_speed_monitor_tests)
