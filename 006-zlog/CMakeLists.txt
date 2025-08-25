cmake_minimum_required(VERSION 3.16)

project(example)
include_directories(.)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} zlog)