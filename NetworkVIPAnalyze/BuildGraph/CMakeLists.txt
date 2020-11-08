cmake_minimum_required(VERSION 3.17)
project(BuildGraph)

set(CMAKE_CXX_STANDARD 11)

add_executable(BuildGraph buildgraph.cpp Matrix.cpp Matrix.h
        List.h
        AutoMachine.h
        AutoMachine.cpp AC_automachine.cpp AC_automachine.h queue.cpp queue.h hash.h)