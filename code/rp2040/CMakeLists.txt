#--------------------------------------------------------------------------------------------------
# Basic
#--------------------------------------------------------------------------------------------------
# Setup the minimum version required of CMake to generate the Makefile
cmake_minimum_required(VERSION 3.25)
# Raises a FATAL_ERROR if version < specified version
cmake_minimum_required (VERSION 3.25 FATAL_ERROR)

# Pull in SDK (must be before project)
#include(stm32cubeh7_sdk.cmake)
include(pico_sdk.cmake)
add_compile_definitions(PICO_XOSC_STARTUP_DELAY_MULTIPLIER=64) # facilitate crystal startup issues

# Initialize the Raspberry Pico SDK
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()
pico_sdk_init()

# Set the project name
project(avs C CXX ASM)

# Set the language standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
)

#--------------------------------------------------------------------------------------------------
# Targets
#--------------------------------------------------------------------------------------------------
# Subdirectories to compile (Projects)
add_subdirectory(lib)
add_subdirectory(src)
