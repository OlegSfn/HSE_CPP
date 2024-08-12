cmake_minimum_required(VERSION 3.27)
project(BigInteger)

set(CMAKE_CXX_STANDARD 17)

add_executable(BigInteger
        big_integer.h
        big_integer.cpp
        big_integer_test.cpp
)
