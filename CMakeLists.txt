cmake_minimum_required(VERSION 2.6)
project(cJson_test C)

#if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -pedantic -Wall")
#    endif()

SET(CMAKE_BUILD_TYPE "DEBUG")
add_library(cJson cJson.c)
add_executable(cJson_test test.c)
target_link_libraries(cJson_test cJson)