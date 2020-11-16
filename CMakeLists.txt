cmake_minimum_required(VERSION 3.13)

project(flurlicht LANGUAGES CXX VERSION 0.1.0)

SET(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(Boost 1.67 COMPONENTS log REQUIRED)

add_subdirectory(extern/pigpio)
add_subdirectory(extern/rpi_ws281x)

include_directories(include)
include_directories(extern)


set(HEADER_FILES include/flurlicht.h include/leds.h)
set(SOURCES src/flurlicht.cpp src/leds.cpp)

add_library(flurlichtlib ${HEADER_FILES} ${SOURCES})

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} pigpio ws2811 flurlichtlib Threads::Threads)
