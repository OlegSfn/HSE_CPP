cmake_minimum_required(VERSION 3.27)
project(Range)

set(CMAKE_CXX_STANDARD 17)

add_executable(Range
        range.h
        range.cpp
        range_public_test.cpp)
