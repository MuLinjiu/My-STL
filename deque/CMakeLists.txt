cmake_minimum_required(VERSION 3.16)
project(deque)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(data)

add_executable(deque
        data/two.memcheck/code.cpp
        data/class-bint.hpp
        data/class-integer.hpp
        data/class-matrix.hpp
        deque.hpp
        exceptions.hpp
        utility.hpp)
