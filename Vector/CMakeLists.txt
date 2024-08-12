cmake_minimum_required(VERSION 3.27)
project(Vector)

set(CMAKE_CXX_STANDARD 17)

add_executable(Vector
        vector.h
        vector_public_test.cpp
)
