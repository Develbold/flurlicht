cmake_minimum_required(VERSION 3.5)

project(flurlicht LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(flurlichtlib flurlicht.cpp)

add_executable(flurlicht main.cpp)

target_link_libraries(flurlicht flurlichtlib)
