cmake_minimum_required(VERSION 3.28)
project(LibManagement C)

set(CMAKE_C_STANDARD 11)

add_executable(LibManagement main.c
        libmanage.h
        libmanage.c)

