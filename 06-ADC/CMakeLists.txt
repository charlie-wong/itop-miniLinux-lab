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
project (adc)

# add the executable
add_executable(adc adc.c)

