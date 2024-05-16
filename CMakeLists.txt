cmake_minimum_required(VERSION 3.27)
project(Lab7 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Lab7
        lab7.c
        tree.c
        tree.h)
