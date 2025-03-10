cmake_minimum_required(VERSION 3.16)

project(dance_partner)
include_directories(.)

add_executable(${PROJECT_NAME} main.c sq_queue.c)