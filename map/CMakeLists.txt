cmake_minimum_required(VERSION 3.16)
project(map)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(data)

add_executable(map
        data/two/code.cpp
        data/class-bint.hpp
        data/class-integer.hpp
        data/class-matrix.hpp
        exceptions.hpp
        map.hpp
        utility.hpp)
