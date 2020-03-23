cmake_minimum_required(VERSION 3.13)
project(salesman)

set(CMAKE_CXX_STANDARD 14)

add_executable(salesman tsp.cpp tsp.hpp)