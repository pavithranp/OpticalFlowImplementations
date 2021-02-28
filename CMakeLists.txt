cmake_minimum_required(VERSION 3.0.0)
project(opticalFlow VERSION 0.1.0)

include_directories("data")
include_directories("lib")
include_directories("lib/stb")
include_directories("lib/eigen")
include_directories("src")
include_directories("src/*")
include_directories("src/*/*")
enable_testing()
file(GLOB SOURCES
    lib/*.h
    lib/*.cpp
    lib/stb/*.h
    src/*.h
    src/*.cpp
    src/*/*.cpp
    src/*/*.h
)
add_executable(opticalFlow main.cpp ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")
