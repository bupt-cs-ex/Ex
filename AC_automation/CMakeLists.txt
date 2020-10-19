cmake_minimum_required(VERSION 3.17)
project(AC_automation)

set(CMAKE_CXX_STANDARD 11)

add_executable(AC_automation main.cpp AC_automation.cpp AC_automation.h queue.cpp queue.h List.h)