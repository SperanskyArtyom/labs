cmake_minimum_required(VERSION 3.22)

project(Fox-Rabbits)

include_directories(lib)

add_executable(${PROJECT_NAME} src/main.cpp
                lib/Animal.h
                lib/Rabbit.h
                lib/Fox.h
                lib/Model.h)
