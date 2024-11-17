cmake_minimum_required(VERSION 3.10)
project(CustomStackProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/CustomMemoryResource.cpp
    src/main.cpp
)

add_executable(CustomStackExecutable ${SOURCES})

set(TEST_SOURCES
    src/CustomMemoryResource.cpp
    tests/test_main.cpp
)

add_executable(StackTests ${TEST_SOURCES})

option(BUILD_TESTS "Build the tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_test(NAME StackTests COMMAND StackTests)
endif()
