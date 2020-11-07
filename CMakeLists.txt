cmake_minimum_required(VERSION 3.5)

project(flurlicht LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(flurlichtlib flurlicht.cpp flurlicht.h)

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#target_link_libraries(${PROJECT_NAME} PRIVATE pigpio flurlichtlib)
target_link_libraries(${PROJECT_NAME} PRIVATE flurlichtlib)
