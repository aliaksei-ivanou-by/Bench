cmake_minimum_required(VERSION 3.20)

project(E506LiveCodingSolutions LANGUAGES CXX)

enable_testing()
find_package(GTest CONFIG REQUIRED)

add_subdirectory(01-aeb-request-gate)
add_subdirectory(02-wheel-speed-plausibility-monitor)
add_subdirectory(03-steering-command-limiter)
add_subdirectory(04-battery-thermal-protection-supervisor)
add_subdirectory(05-parking-assist-warning-coordinator)
add_subdirectory(06-cabin-ambient-light-controller)
