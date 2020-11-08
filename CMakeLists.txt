cmake_minimum_required(VERSION 3.13)

project(flurlicht LANGUAGES CXX C)

# Define our host system
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)

# define cross compile tools folder
set(RP_TOOLS_DIR "")



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_subdirectory(extern/pigpio/)
#add_subdirectory(extern/rpi_ws281x/)

add_library(flurlichtlib flurlicht.cpp flurlicht.h leds.cpp leds.h)

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE pigpio flurlichtlib Threads::Threads)
#target_link_libraries(${PROJECT_NAME} PRIVATE flurlichtlib)
