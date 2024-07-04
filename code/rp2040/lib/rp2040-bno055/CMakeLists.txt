include_directories(include)

# Set the name
set(LIB_NAME rp2040-bno055)

# Automatically collect all C source files in the src/ directory
file(GLOB LIB_SOURCES "src/*.c")

# Create the library
add_library(${LIB_NAME} ${LIB_SOURCES})

# Include directories for the library
target_include_directories(${LIB_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    # Add other include directories if necessary
)

# Add the standard library to the build
target_link_libraries(${LIB_NAME}
    hardware_i2c
    pico_stdlib
)
