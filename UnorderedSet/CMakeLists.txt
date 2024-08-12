cmake_minimum_required(VERSION 3.27)
project(UnorderedSet)

set(CMAKE_CXX_STANDARD 17)

add_executable(UnorderedSet
        unordered_set.h
        unordered_set_public_test.cpp)
