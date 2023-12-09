cmake_minimum_required(VERSION 3.24)
project(IMS)

set(CMAKE_CXX_STANDARD 17)

add_executable(IMS main.cpp cell.cpp cell.h grid.cpp grid.h image.cpp image.h)

