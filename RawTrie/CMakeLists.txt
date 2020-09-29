cmake_minimum_required(VERSION 3.17)
project(RawTrie)

set(CMAKE_CXX_STANDARD 11)

add_executable(RawTrie rawtrie.cpp Trie.cpp Trie.h)