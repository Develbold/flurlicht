cmake_minimum_required(VERSION 3.13)

project(flurlicht LANGUAGES CXX VERSION 0.1.0)

SET(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
#SET (CMAKE_C_COMPILER             "/usr/bin/clang")
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

find_package(Threads REQUIRED)
set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost COMPONENTS log regex REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(PahoMqttCpp REQUIRED)

add_subdirectory(extern/pigpio)
add_subdirectory(extern/rpi_ws281x_static)

include_directories(include)
include_directories(extern)
include_directories(tests)

#code coverage
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)
include(CodeCoverage)
append_coverage_compiler_flags()
#setup_target_for_coverage_gcovr_html(${PROJECT_NAME}_coverage ${PROJECT_TEST_NAME} coverage)
SETUP_TARGET_FOR_COVERAGE_LCOV(NAME ${PROJECT_NAME}_coverage
                              EXECUTABLE runUnitTests
                              DEPENDENCIES ${PROJECT_NAME}
                              EXCLUDE "/usr/include/*" "boost/" "extern/" "googletest/")
#target_link_libraries(${PROJECT_TEST_NAME} gcov)


################################
# GTest
################################
ADD_SUBDIRECTORY (extern/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCES tests/runTests.cpp
                tests/flurlicht_tools_test.cpp
                tests/leds_test.cpp)

set(HEADER_FILES include/flurlicht.h
                include/flurlicht_tools.h
                include/flurlicht_gpio.h
                include/flurlicht_mqtt.h
                include/flurlicht_events.h
                include/leds.h
                include/animations_base.h
                include/animations_random.h
                include/animations_random_granular.h
                include/animations_allfade.h
                include/animations_blink.h
                include/animations_scanner.h)

set(SOURCES src/flurlicht.cpp
            src/flurlicht_tools.cpp
            src/flurlicht_gpio.cpp
            src/flurlicht_mqtt.cpp
            src/flurlicht_events.cpp
            src/leds.cpp
            src/animations_base.cpp
            src/animations_random.cpp
            src/animations_random_granular.cpp
            src/animations_allfade.cpp
            src/animations_blink.cpp
            src/animations_scanner.cpp)

#add_library(flurlichtlib ${HEADER_FILES} ${SOURCES})

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} Boost::log ws2811 pigpio Threads::Threads paho-mqtt3as paho-mqttpp3)

#################################
## Unit Tests
#################################
## Add test cpp file
#add_executable( runUnitTests ${TEST_SOURCES} ${SOURCES})
## Link test executable against gtest & gtest_main
#target_link_libraries(runUnitTests gtest gtest_main pigpio Boost::log ws2811 paho-mqtt3a)
#add_test( runUnitTests runUnitTests )
