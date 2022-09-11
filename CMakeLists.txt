cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(cJson CXX)

# enable c++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# take respectives flags for debug & release process
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-std=c++11 -g -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-std=c++11 -g -O2")

# default build type : Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif ()

find_package(GTest REQUIRED)

find_library(GMOCK
        NAMES gmock
        PATH /usr/local/lib /usr/lib)

include_directories(${PROJECT_SOURCE_DIR}/src)

# CTest related
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})
add_subdirectory(tests)