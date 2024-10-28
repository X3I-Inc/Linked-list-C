cmake_minimum_required(VERSION 3.29)
project(Linked_list_C C)

set(CMAKE_C_STANDARD 11)

include_directories(ex2)

add_executable(Linked_list_C
    ex2/dplist.h
    ex2/dplist2.c
    ex2/program.c)
