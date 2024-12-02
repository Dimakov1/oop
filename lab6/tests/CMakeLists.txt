cmake_minimum_required(VERSION 3.5)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR}/../include)

set(TEST_SOURCES
    test.cpp
    ../src/Subject.cpp
    ../src/ConsoleLogger.cpp
    ../src/FileLogger.cpp
    ../src/NPC.cpp
    ../src/Dragon.cpp
    ../src/Bull.cpp
    ../src/Toad.cpp
    ../src/NPCFactory.cpp
)

add_executable(runTests ${TEST_SOURCES})

target_link_libraries(runTests gtest gtest_main)

add_test(NAME runTests COMMAND runTests)
