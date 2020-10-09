cmake_minimum_required(VERSION 3.17)
project(RadixTree)

set(CMAKE_CXX_STANDARD 14)

add_executable(RadixTree radix_search.cpp RadixTree.h RadixTree.cpp)