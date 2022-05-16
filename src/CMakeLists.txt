cmake_minimum_required(VERSION 3.13)
project(mc LANGUAGES CXX)

add_executable(mc.out
        main.cpp
)

target_link_libraries(mc.out PRIVATE vectorizer markov_chain )

target_compile_options(mc.out PRIVATE -Wall -pedantic -pipe)
