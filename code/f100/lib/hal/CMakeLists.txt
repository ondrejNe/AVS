set(HAL_DRIVERS_PATH ${stm32_hal_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver)
set(CMSIS_PATH ${stm32_hal_SOURCE_DIR}/Drivers/CMSIS)

file(GLOB HAL_SOURCES ${HAL_DRIVERS_PATH}/Src/*.c)
list(FILTER HAL_SOURCES EXCLUDE REGEX ".*_template.c$")

add_library(lib_hal STATIC ${HAL_SOURCES})

target_include_directories(lib_hal PUBLIC
        .
        ${HAL_DRIVERS_PATH}/Inc
        ${CMSIS_PATH}/Include
        ${CMSIS_PATH}/Device/ST/STM32F1xx/Include
)
