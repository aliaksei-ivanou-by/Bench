cmake_minimum_required(VERSION 3.20)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(ParkingAssistCoordinatorExercise LANGUAGES CXX)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif()

set(PARKING_ASSIST_IMPLEMENTATION
    "${CMAKE_CURRENT_SOURCE_DIR}/solution/ParkingAssistCoordinator.cpp"
    CACHE FILEPATH "Parking-assist implementation compiled by the exercise")

add_library(e506_parking_assist_coordinator STATIC
    ${PARKING_ASSIST_IMPLEMENTATION})
target_include_directories(e506_parking_assist_coordinator PUBLIC include)
target_compile_features(e506_parking_assist_coordinator PUBLIC cxx_std_17)

add_executable(e506_parking_assist_coordinator_tests
    tests/ParkingAssistCoordinatorTest.cpp)
target_link_libraries(e506_parking_assist_coordinator_tests
    PRIVATE e506_parking_assist_coordinator GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(e506_parking_assist_coordinator_tests)
