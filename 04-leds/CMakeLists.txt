cmake_minimum_required (VERSION 2.6)
###########################################
# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
# specify the cross compiler
SET(CMAKE_C_COMPILER   /usr/local/arm/arm-2009q3/bin/arm-none-linux-gnueabi-gcc)
SET(CMAKE_CXX_COMPILER /usr/local/arm/arm-2009q3/bin/arm-none-linux-gnueabi-g++)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  /usr/local/arm/arm-2009q3)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

###########################################
project (leds)

# The version number.
set (LEDS_VERSION_MAJOR 0)
set (LEDS_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config/ledsConfig.h.in"
  "${PROJECT_BINARY_DIR}/config/ledsConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}/config")

# add the executable
add_executable(leds leds.c)

