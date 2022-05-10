cmake_minimum_required(VERSION 3.13)

project(nn LANGUAGES CXX)

add_library(nn SHARED
    nn.cpp
 )

target_include_directories(nn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_SOURCE_DIR})