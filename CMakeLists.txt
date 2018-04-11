cmake_minimum_required(VERSION 3.8)
project(Lab_3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        CInterface.cpp
        "../Lab4 actual/dane.txt"
        CInterface.h
        CNode.cpp
        CNode.h
        CTree.cpp
        CTree.h
        main.cpp "../Lab4 actual/GeneticTree.cpp" "../Lab4 actual/GeneticTree.h")

add_executable(Lab_3 ${SOURCE_FILES})