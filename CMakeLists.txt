cmake_minimum_required(VERSION 3.13)

project(flurlicht LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_subdirectory(extern/pigpio)
#add_subdirectory(extern/rpi_ws281x/)

include_directories(include)
include_directories(extern)

set(HEADER_FILES include/flurlicht.h include/leds.h)
set(SOURCES src/flurlicht.cpp src/leds.cpp)

add_library(flurlichtlib ${HEADER_FILES} ${SOURCES})

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE pigpio flurlichtlib Threads::Threads)
