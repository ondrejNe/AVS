
set(NAME can)
file(GLOB SOURCES src/*.c)
add_executable(${NAME} ${SOURCES})
include_directories(include)
target_link_libraries(${NAME}
        lib_bsp
        lib_startup
)
