cmake_minimum_required(VERSION 3.16)

project(bracket_match)
include_directories(.)

add_executable(${PROJECT_NAME} main.c sq_stack.c)