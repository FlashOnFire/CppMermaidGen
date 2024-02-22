cmake_minimum_required(VERSION 3.28)
project(CppMermaidGen)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppMermaidGen main.cpp
        Utils.h
        Class.cpp
        Class.h
        Function.cpp
        Function.h
        ClassDiagram.cpp
        ClassDiagram.h)
