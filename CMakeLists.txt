cmake_minimum_required(VERSION 3.0.0)
project(opticalFlow VERSION 0.1.0)

include_directories("data")
include_directories("lib")
include_directories("lib/eigen")
enable_testing()
file(GLOB SOURCES
    lib/*.h
    lib/*.cpp
    lib/stb/*.h
    src/*.h
    src/*.cpp
)
add_executable(opticalFlow main.cpp ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
