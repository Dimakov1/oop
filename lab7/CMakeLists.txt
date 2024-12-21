cmake_minimum_required(VERSION 3.5)
project(lab7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    main.cpp
    src/NPC.cpp
    src/Dragon.cpp
    src/Bull.cpp
    src/Toad.cpp
    src/NPCFactory.cpp
)

add_executable(game ${SOURCES})

if (WIN32)
    target_link_libraries(game Threads::Threads)
else()
    target_link_libraries(game pthread)
endif()
