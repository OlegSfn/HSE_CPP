cmake_minimum_required(VERSION 3.27)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(Matrix
        matrix.h
        rational.h
        my_fraction.cpp
        matrix_test.cpp)
