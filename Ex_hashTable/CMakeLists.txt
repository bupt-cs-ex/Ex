cmake_minimum_required(VERSION 3.17)
project(Ex_hashTable)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Ex_hashTable
        dict.txt
        HashTable.cpp
        HashTable.h
        "hashtable_search .cpp"
        result.txt
        string.txt BloomFilter.cpp BloomFilter.h
        MurmurHash3.h
        MurmurHash3.cpp)
