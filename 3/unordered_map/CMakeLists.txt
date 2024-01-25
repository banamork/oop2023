cmake_minimum_required(VERSION 3.16)
project(unordered_map)

set(CMAKE_CXX_STANDARD 20)

add_library(unordered_map INTERFACE)

target_include_directories(unordered_map INTERFACE include)
