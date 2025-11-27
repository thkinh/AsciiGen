cmake_minimum_required(VERSION 4.0)
project(ascii_gen)

set(CMAKE_CXX_STANDARD 17)

#include_directories(include)
include_directories(external/stb)
file(GLOB SOURCES "src/*.cpp" "external/stb/stb_impl.cpp")

add_executable(ascii_gen ${SOURCES})

