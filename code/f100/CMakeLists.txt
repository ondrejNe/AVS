cmake_minimum_required(VERSION 3.25)

###################### Framework ######################################
include(FetchContent)
FetchContent_Declare(stm32_hal
        GIT_REPOSITORY https://github.com/STMicroelectronics/STM32CubeF1.git
        GIT_TAG v1.8.5
)
FetchContent_MakeAvailable(stm32_hal)

################## PROJECT SETUP ######################################
# Include the subdirectories for each module
project("f100" C CXX ASM)

# Set suffixes for executable and static libraries
set(CMAKE_EXECUTABLE_SUFFIX     ".elf")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")

add_subdirectory(lib)
add_subdirectory(demo)

message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Executable Suffix: ${CMAKE_EXECUTABLE_SUFFIX}")
