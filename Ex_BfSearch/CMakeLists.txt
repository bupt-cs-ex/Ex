cmake_minimum_required(VERSION 3.17)
project(Ex_BfSearch)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Ex_BfSearch
        bf_search.cpp
        BloomFilter.cpp
        BloomFilter.h
        dict.txt
        MurmurHash3.cpp
        MurmurHash3.h
        result.txt
        string.txt)
