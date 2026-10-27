cmake_minimum_required(VERSION 3.20)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    project(AmbientLightControllerExercise LANGUAGES CXX)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif()

set(AMBIENT_LIGHT_IMPLEMENTATION
    "${CMAKE_CURRENT_SOURCE_DIR}/solution/AmbientLightController.cpp"
    CACHE FILEPATH "Ambient-light implementation compiled by the exercise")

add_library(e506_ambient_light_controller STATIC
    ${AMBIENT_LIGHT_IMPLEMENTATION})
target_include_directories(e506_ambient_light_controller PUBLIC include)
target_compile_features(e506_ambient_light_controller PUBLIC cxx_std_17)

add_executable(e506_ambient_light_controller_tests
    tests/AmbientLightControllerTest.cpp)
target_link_libraries(e506_ambient_light_controller_tests
    PRIVATE e506_ambient_light_controller GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(e506_ambient_light_controller_tests)
