set(NAME lib_lcd)

file(GLOB SOURCES *.c)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC
        .
)
target_link_libraries(${NAME}
        lib_hal
)
