cmake_minimum_required(VERSION 3.20)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(AebRequestGateExercise LANGUAGES CXX)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif()

set(AEB_IMPLEMENTATION
    "${CMAKE_CURRENT_SOURCE_DIR}/solution/AebRequestGate.cpp"
    CACHE FILEPATH "AEB implementation compiled by the exercise")

add_library(e506_aeb_request_gate STATIC ${AEB_IMPLEMENTATION})
target_include_directories(e506_aeb_request_gate PUBLIC include)
target_compile_features(e506_aeb_request_gate PUBLIC cxx_std_17)

add_executable(e506_aeb_request_gate_tests tests/AebRequestGateTest.cpp)
target_link_libraries(e506_aeb_request_gate_tests
    PRIVATE e506_aeb_request_gate GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(e506_aeb_request_gate_tests)
