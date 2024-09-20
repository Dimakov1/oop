cmake_minimum_required(VERSION 3.10)

project(test_Cmake)

add_executable(main_exe src/main.cpp src/calculator.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests tests/tests.cpp src/calculator.cpp)
target_link_libraries(tests gtest gtest_main)
add_test(NAME CalculatorTest COMMAND tests)