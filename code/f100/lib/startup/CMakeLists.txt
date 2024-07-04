
set(NAME lib_startup)

file(GLOB SOURCES *.c *.s)

add_library(${NAME} STATIC ${SOURCES})
target_link_libraries(${NAME}
        lib_hal
)
