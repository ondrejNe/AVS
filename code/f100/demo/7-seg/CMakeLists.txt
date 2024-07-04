
set(NAME 7-seg)
file(GLOB SOURCES src/*.c)
add_executable(${NAME} ${SOURCES})
include_directories(include)
target_link_libraries(${NAME}
        lib_bsp
        lib_hal
        lib_startup
        lib_7_seg
)
