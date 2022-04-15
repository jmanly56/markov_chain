cmake_minimum_required(VERSION 3.13)

add_subdirectory(vectorizer)
add_subdirectory(markov_chain)

project(markov_chain++ LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(mc.out
        main.cpp
)

target_link_libraries(mc.out PRIVATE vectorizer markov_chain "-Wl")

target_compile_options(mc.out PRIVATE -Wall -pedantic -pipe)
