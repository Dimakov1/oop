cmake_minimum_required(VERSION 3.10)

project(lab4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main_exe main.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lab4_tests tests/test.cpp)

target_include_directories(lab4_tests PRIVATE include)

target_link_libraries(lab4_tests gtest gtest_main)
add_test(NAME Lab4Tests COMMAND lab4_tests)
