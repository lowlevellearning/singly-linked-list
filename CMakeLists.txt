cmake_minimum_required(VERSION 3.26)
project(singly_linked_list C)

set(CMAKE_C_STANDARD 23)

include_directories(.)

add_executable(singly_linked_list
        main.c
        main.h)
