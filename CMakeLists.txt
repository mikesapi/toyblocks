cmake_minimum_required(VERSION 2.8.12)

add_compile_options(-std=c++11 -Wall)

project(toyblocks)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/bin")

set(targetname toyblocks)

set(sources
main.cpp
)

add_executable(${targetname} ${sources})
