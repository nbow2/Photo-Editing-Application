cmake_minimum_required(VERSION 3.26)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp bmplib.cpp bmplib.h
        bmplib.h
        Filter.cpp
        Filter.h)
