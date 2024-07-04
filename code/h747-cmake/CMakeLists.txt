cmake_minimum_required(VERSION 3.25)

###################### VARIABLES ######################################
set(PROJECT_NAME                "test")
set(PROJECT_TYPE                "exe")
set(LINKER_SCRIPT               "../STM32H747XIHX_FLASH.ld")
set(MCPU                        "-mcpu=cortex-m7")
set(MFPU                        "-mfpu=fpv5-d16")
set(MFLOAT_ABI                  "-mfloat-abi=hard")
set(RUNTIME_LIBRARY             "--specs=nano.specs")
set(RUNTIME_LIBRARY_SYSCALLS    "--specs=nosys.specs")
###################### TOOLCHAIN & Global deps ########################
enable_language(ASM)

include(FetchContent)
FetchContent_Declare(
        stm32_hal
        GIT_REPOSITORY https://github.com/STMicroelectronics/STM32CubeH7.git
        GIT_TAG v1.11.2
)
FetchContent_MakeAvailable(stm32_hal)

set(BSP_DRIVERS_PATH ${stm32_hal_SOURCE_DIR}/Drivers/BSP)
set(CMSIS_PATH ${stm32_hal_SOURCE_DIR}/Drivers/CMSIS)
set(HAL_DRIVERS_PATH ${stm32_hal_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver)
set(UTILS_PATH ${stm32_hal_SOURCE_DIR}/Utilities)
###################### Sources ########################################
set(PROJECT_DEFINES
        -DUSE_HAL_DRIVER
        -DSTM32H747xx
        -DCORE_CM7
)

set(PROJECT_SOURCES
        Startup/startup_stm32h747xihx.s

        Sources/main.c
        Sources/stm32h7xx_hal_msp.c
        Sources/stm32h7xx_it.c
        Sources/syscalls.c
        Sources/sysmem.c
        Sources/system_stm32h7xx.c
)

set(PROJECT_INCLUDES
        Include
)

set(BSP_SOURCES
        ${BSP_DRIVERS_PATH}/Components/otm8009a/otm8009a.c
        ${BSP_DRIVERS_PATH}/Components/otm8009a/otm8009a_reg.c
        ${BSP_DRIVERS_PATH}/Components/nt35510/nt35510.c
        ${BSP_DRIVERS_PATH}/Components/nt35510/nt35510_reg.c
        ${BSP_DRIVERS_PATH}/Components/is42s32800j/is42s32800j.c

        ${BSP_DRIVERS_PATH}/STM32H747I-DISCO/stm32h747i_discovery.c
        ${BSP_DRIVERS_PATH}/STM32H747I-DISCO/stm32h747i_discovery_bus.c
        ${BSP_DRIVERS_PATH}/STM32H747I-DISCO/stm32h747i_discovery_lcd.c
        ${BSP_DRIVERS_PATH}/STM32H747I-DISCO/stm32h747i_discovery_sdram.c
)

set(UTILS_SOURCES ${UTILS_PATH}/lcd/stm32_lcd.c)
file(GLOB HAL_SOURCES ${HAL_DRIVERS_PATH}/Src/*.c)
list(APPEND PROJECT_SOURCES ${BSP_SOURCES} ${HAL_SOURCES} ${UTILS_SOURCES})
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*_template.c$")

list(APPEND PROJECT_INCLUDES
        ${BSP_DRIVERS_PATH}/Components/Common
        ${BSP_DRIVERS_PATH}/Components/otm8009a
        ${BSP_DRIVERS_PATH}/Components/nt35510
        ${BSP_DRIVERS_PATH}/Components/is42s32800j
        ${BSP_DRIVERS_PATH}/STM32H747I-DISCO
        ${CMSIS_PATH}/Include
        ${CMSIS_PATH}/Device/ST/STM32H7xx/Include
        ${HAL_DRIVERS_PATH}/Inc
        ${UTILS_PATH}/lcd
)
################## PROJECT SETUP ######################################
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)

add_compile_definitions(${PROJECT_DEFINES})
include_directories(${PROJECT_INCLUDES})

set(CMAKE_EXECUTABLE_SUFFIX         ".elf")
set(CMAKE_STATIC_LIBRARY_SUFFIX     ".a")
set(CMAKE_C_FLAGS                   "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Werror"
)
set(CMAKE_EXE_LINKER_FLAGS          "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections -static -Wl,--start-group -lc -lm -Wl,--end-group")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")

# Custom target for flashing using OpenOCD
add_custom_target(flash
        COMMAND openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c "program ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf verify reset exit"
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Flashing ${PROJECT_NAME}.elf to the target"
)

# Custom target for starting OpenOCD
add_custom_target(openocd
        COMMAND openocd -f interface/stlink.cfg -f target/stm32h7x.cfg
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Starting OpenOCD"
)

# Custom target for debugging with GDB
add_custom_target(debug
        COMMAND arm-none-eabi-gdb -q -x ${CMAKE_SOURCE_DIR}/gdbinit ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf
        DEPENDS ${PROJECT_NAME}
        COMMENT "Starting GDB for debugging"
)
