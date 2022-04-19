cmake_minimum_required(VERSION 3.13)

project(markov_chain LANGUAGES CXX)


add_library(markov_chain SHARED
    "include/markov_chain.h"
    "markov_chain.cpp"
)

set_target_properties(markov_chain PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/markov_chain.h)

target_include_directories(markov_chain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)