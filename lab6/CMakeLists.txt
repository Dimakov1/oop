cmake_minimum_required(VERSION 3.5)
project(lab6)

set(CMAKE_CXX_STANDARD 11)

if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    main.cpp
    src/Subject.cpp
    src/ConsoleLogger.cpp
    src/FileLogger.cpp
    src/NPC.cpp
    src/Dragon.cpp
    src/Bull.cpp
    src/Toad.cpp
    src/NPCFactory.cpp
)

add_executable(game_editor ${SOURCES})

enable_testing()
add_subdirectory(tests)
