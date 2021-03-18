# Install script for directory: /home/stephan/workspace/misc_cpp/flurlicht/extern/rpi_ws281x_static

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/stephan/workspace/misc_cpp/flurlicht/extern/rpi_ws281x_static/libws2811.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ws2811" TYPE FILE FILES
    "/home/stephan/workspace/misc_cpp/flurlicht/extern/rpi_ws281x_static/ws2811.h"
    "/home/stephan/workspace/misc_cpp/flurlicht/extern/rpi_ws281x_static/rpihw.h"
    "/home/stephan/workspace/misc_cpp/flurlicht/extern/rpi_ws281x_static/pwm.h"
    "/home/stephan/workspace/misc_cpp/flurlicht/extern/rpi_ws281x_static/clk.h"
    "/home/stephan/workspace/misc_cpp/flurlicht/extern/rpi_ws281x_static/dma.h"
    "/home/stephan/workspace/misc_cpp/flurlicht/extern/rpi_ws281x_static/gpio.h"
    "/home/stephan/workspace/misc_cpp/flurlicht/extern/rpi_ws281x_static/mailbox.h"
    "/home/stephan/workspace/misc_cpp/flurlicht/extern/rpi_ws281x_static/pcm.h"
    )
endif()

