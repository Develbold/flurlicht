cmake_minimum_required(VERSION 3.13)

project(flurlicht LANGUAGES CXX VERSION 0.1.0)

SET(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_subdirectory(extern/pigpio)
add_subdirectory(extern/rpi_ws281x)

include_directories(include)
include_directories(extern)

#include_directories(${rpi_ws281x_INCLUDE_DIRS})
#link_directories(${rpi_ws281x_LIBRARY_DIRS})

#file(GLOB_RECURSE PIGPIO_SRC_FILES extern/pigpio/*.c)
#file(GLOB_RECURSE PIGPIO_HEADER_FILES extern/pigpio/*.h)

#message(STATUS ${PIGPIO_SRC_FILES})
#message(STATUS ${PIGPIO_HEADER_FILES})


set(HEADER_FILES include/flurlicht.h include/leds.h)
#${PIGPIO_HEADER_FILES})
set(SOURCES src/flurlicht.cpp src/leds.cpp)
# ${PIGPIO_SRC_FILES})

#message(STATUS ${HEADER_FILES})

add_library(flurlichtlib ${HEADER_FILES} ${SOURCES})

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

#find_library(PIGPIO libpigpio.a)

target_link_libraries(${PROJECT_NAME} pigpio ws2811 flurlichtlib Threads::Threads)
