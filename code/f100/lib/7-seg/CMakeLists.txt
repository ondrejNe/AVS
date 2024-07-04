
set(NAME lib_7_seg)

file(GLOB SOURCES *.c)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC
        .
)
target_link_libraries(${NAME}
        lib_hal
)
