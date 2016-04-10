# Find the STM32 CMSIS and StdPeriph libraries

find_path(STM32_LIBRARY_ROOT_DIR
    Drivers/CMSIS/Include/core_cm4.h
    Drivers/STM32F4xx_HAL_Driver/Inc/stm32f4xx_hal_gpio.h
    DOC "STM32 libraries root directory: STM32F4xx_DSP_StdPeriph_Lib_V1.0.1/Libraries"
    )

set(STM32_STARTUP_SOURCE ${STM32_LIBRARY_ROOT_DIR}/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f429xx.s)

set(STM32_INCLUDE_DIRS
    ${STM32_LIBRARY_ROOT_DIR}/CMSIS/Include
    ${STM32_LIBRARY_ROOT_DIR}/CMSIS/Device/ST/STM32F4xx/Include
    ${STM32_LIBRARY_ROOT_DIR}/STM32F4xx_HAL_Driver/Inc
    )

file(GLOB STM32_SOURCES ${STM32_LIBRARY_ROOT_DIR}/STM32F4xx_HAL_Driver/Src/*.c)

find_package(PackageHandleStandardArgs)
find_package_handle_standard_args(CMSIS DEFAULT_MSG
        STM32_LIBRARY_ROOT_DIR
        STM32_STARTUP_SOURCE
        STM32_SOURCES
        STM32_INCLUDE_DIRS
        )

