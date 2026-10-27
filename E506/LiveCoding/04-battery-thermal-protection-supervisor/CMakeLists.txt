cmake_minimum_required(VERSION 3.20)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(BatteryThermalSupervisorExercise LANGUAGES CXX)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif()

set(BATTERY_THERMAL_IMPLEMENTATION
    "${CMAKE_CURRENT_SOURCE_DIR}/solution/BatteryThermalSupervisor.cpp"
    CACHE FILEPATH "Battery thermal implementation compiled by the exercise")

add_library(e506_battery_thermal_supervisor STATIC
    ${BATTERY_THERMAL_IMPLEMENTATION})
target_include_directories(e506_battery_thermal_supervisor PUBLIC include)
target_compile_features(e506_battery_thermal_supervisor PUBLIC cxx_std_17)

add_executable(e506_battery_thermal_supervisor_tests
    tests/BatteryThermalSupervisorTest.cpp)
target_link_libraries(e506_battery_thermal_supervisor_tests
    PRIVATE e506_battery_thermal_supervisor GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(e506_battery_thermal_supervisor_tests)
