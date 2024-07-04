# toolchain.cmake
set(CMAKE_SYSTEM_NAME       Generic)
set(CMAKE_SYSTEM_PROCESSOR  arm)

# Automatically find the compilers and tools
find_program(CMAKE_C_COMPILER   arm-none-eabi-gcc REQUIRED)
find_program(CMAKE_CXX_COMPILER arm-none-eabi-g++ REQUIRED)

find_program(CMAKE_LINKER       arm-none-eabi-ld)
find_program(CMAKE_AR           arm-none-eabi-ar)
find_program(CMAKE_OBJCOPY      arm-none-eabi-objcopy)
find_program(CMAKE_OBJDUMP      arm-none-eabi-objdump)
find_program(CMAKE_SIZE         arm-none-eabi-size)
find_program(CMAKE_RANLIB       arm-none-eabi-ranlib)
find_program(CMAKE_STRIP        arm-none-eabi-strip)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Compilation flags
set(MFLOAT_ABI                  "-mfloat-abi=soft") # no FPU on M3 cores
set(RUNTIME_LIBRARY             "--specs=nano.specs")
set(RUNTIME_LIBRARY_SYSCALLS    "--specs=nosys.specs")

# Compilation flags
set(CMAKE_C_FLAGS      "-mcpu=cortex-m3 -std=gnu11   -mfloat-abi=soft -mthumb -Wall -Werror")
set(CMAKE_CXX_FLAGS    "-mcpu=cortex-m3 -std=gnu++11 -mfloat-abi=soft -mthumb -Wall -Werror ${RUNTIME_LIBRARY}")
set(CMAKE_ASM_FLAGS    "-mcpu=cortex-m3              -mfloat-abi=soft -mthumb -x assembler-with-cpp")

# Linker flags
set(LINKER_SCRIPT           "${CMAKE_SOURCE_DIR}/lib/STM32F100RBTX_FLASH.ld")
set(CMAKE_EXE_LINKER_FLAGS  "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections -static -Wl,--start-group -lc -lm -Wl,--end-group")

set(PROJECT_DEFINES
        -DUSE_HAL_DRIVER
        -DSTM32F100xB
        -DCORE_CM3
)
add_compile_definitions(${PROJECT_DEFINES})
