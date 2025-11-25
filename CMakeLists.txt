cmake_minimum_required(VERSION 4.0)
project(ascii_gen)

set(CMAKE_CXX_STANDARD 20)

#include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(ascii_gen ${SOURCES})

