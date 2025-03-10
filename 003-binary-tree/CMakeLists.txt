cmake_minimum_required(VERSION 3.16)

project(binary_tree)
include_directories(.)

add_executable(${PROJECT_NAME} main.c sq_btree.c)