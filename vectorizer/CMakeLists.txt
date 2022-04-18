cmake_minimum_required(VERSION 3.13)

project(vectorizer LANGUAGES CXX)

add_library(vectorizer SHARED
    include/vectorizer.h
    vectorizer.cpp
)

set_target_properties(vectorizer PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/vectorizer.h)

target_include_directories(vectorizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)