cmake_minimum_required(VERSION 3.17)
project(mTrie)

set(CMAKE_CXX_STANDARD 14)

add_executable(mTrie mtrie.cpp mtrie_define.h mtrie_define.cpp)