include_directories(include)

# Set the name
set(NAME rp2040-bmp-demo)


add_executable(${NAME}
    src/main.c
)

# Add the standard library to the build
target_link_libraries(${NAME}
    hardware_i2c
    pico_stdlib
    rp2040-bmp3
    rp2040-time
)

pico_enable_stdio_usb(${NAME} 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})
