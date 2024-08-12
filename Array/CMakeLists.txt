cmake_minimum_required(VERSION 3.27)
project(Array)

set(CMAKE_CXX_STANDARD 17)

add_executable(Array
        array.h
        array_test.cpp
        catch.hpp)
