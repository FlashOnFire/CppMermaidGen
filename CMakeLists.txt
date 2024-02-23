cmake_minimum_required(VERSION 3.28)
project(CppMermaidGen)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppMermaidGen src/main.cpp
        src/Utils.h
        src/Class.cpp
        src/Class.h
        src/Function.cpp
        src/Function.h
        src/ClassDiagram.cpp
        src/ClassDiagram.h
        src/Link.cpp
        src/Link.h
        src/LinkType.h
        src/Field.cpp
        src/Field.h
        src/ClassType.h
        src/EnumField.cpp
        src/EnumField.h)
