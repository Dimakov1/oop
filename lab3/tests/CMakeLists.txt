cmake_minimum_required(VERSION 3.10)

project(Lab4Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(../include)

set(TEST_SOURCES
    test.cpp
)

add_executable(Lab4Tests ${TEST_SOURCES})
target_link_libraries(Lab4Tests ${GTEST_LIBRARIES} pthread)
