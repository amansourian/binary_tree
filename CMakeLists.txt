cmake_minimum_required(VERSION 3.9)
project(binary_tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(binary_tree
        binarytree.h
        main.cpp
        node.h)
