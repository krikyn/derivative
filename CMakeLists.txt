cmake_minimum_required(VERSION 3.6)
project(laba_dm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(laba_dm ${SOURCE_FILES})