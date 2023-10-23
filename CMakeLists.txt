cmake_minimum_required(VERSION 3.25)
project(singly_linked_list C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES src/*.c src/*.h)
add_executable(${PROJECT_NAME} ${SRC_FILES})
