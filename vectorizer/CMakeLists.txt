cmake_minimum_required(VERSION 3.8)

add_library(vectorizer
    vectorizer.h
    vectorizer.cpp
)

target_include_directories(vectorizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})