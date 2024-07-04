set(BSP_DRIVERS_PATH ${stm32_hal_SOURCE_DIR}/Drivers/BSP)

add_library(lib_bsp STATIC
        ${BSP_DRIVERS_PATH}/STM32VL-Discovery/stm32vl_discovery.c
)

target_include_directories(lib_bsp PUBLIC
        ${BSP_DRIVERS_PATH}/STM32VL-Discovery
)
target_link_libraries(lib_bsp
        lib_hal
)
