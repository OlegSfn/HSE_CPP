cmake_minimum_required(VERSION 3.27)
project(Geometry)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
add_compile_options(-fsanitize=undefined)
add_link_options(-fsanitize=undefined)
add_compile_options(-g)
add_link_options(-g)

add_executable(Geometry
        vector.h
        point.h
        segment.h
        line.h
        ray.h
        polygon.h
        circle.h
        i_shape.h
        src/vector.cpp
        geometry_main.cpp
        src/point.cpp
        src/segment.cpp
        src/line.cpp
        src/ray.cpp
        src/circle.cpp
        src/polygon.cpp)
