cmake_minimum_required(VERSION 3.16)

project(student_management_system)
include_directories(./src)

add_executable(${PROJECT_NAME} src/main.c src/student.c)