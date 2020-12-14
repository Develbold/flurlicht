cmake_minimum_required(VERSION 3.13)

project(flurlicht LANGUAGES CXX VERSION 0.1.0)

SET(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(Threads REQUIRED)
set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost 1.67 COMPONENTS log REQUIRED)

#add_subdirectory(extern/pigpio)
add_subdirectory(extern/rpi_ws281x)

include_directories(include)
include_directories(extern)


set(HEADER_FILES include/flurlicht.h
                include/flurlicht_tools.h
#                include/flurlicht_gpio.h
                include/leds.h
                include/animations_base.h
                include/animations.h
#                include/flurlicht_events.h
                include/flurlicht_arduino.h)

set(SOURCES src/flurlicht.cpp
            src/flurlicht_tools.cpp
#            src/flurlicht_gpio.cpp
            src/leds.cpp
            src/animations_base.cpp
            src/animations.cpp
#            src/flurlicht_events.cpp
            src/flurlicht_arduino.cpp)

#add_library(flurlichtlib ${HEADER_FILES} ${SOURCES})

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} Boost::log ws2811 Threads::Threads)
