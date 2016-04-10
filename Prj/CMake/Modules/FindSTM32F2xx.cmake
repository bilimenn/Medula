# Find the STM32 CMSIS and StdPeriph libraries

find_path(STM32_LIBRARY_ROOT_DIR
    Drv/CMSIS/Include/core_cm4.h
    Drv/STM32F2xx_HAL_Driver/Inc/stm32f2xx_hal_gpio.h
    DOC "STM32 libraries root directory: STM32F2xx_DSP_StdPeriph"
    )

set(STM32_STARTUP_SOURCE ${STM32_LIBRARY_ROOT_DIR}/CMSIS/Device/ST/STM32F2xx/Source/Templates/gcc/startup_stm32f207xx.s)

set(STM32_INCLUDE_DIRS
    ${STM32_LIBRARY_ROOT_DIR}/CMSIS/Include
    ${STM32_LIBRARY_ROOT_DIR}/CMSIS/Device/ST/STM32F2xx/Include
    ${STM32_LIBRARY_ROOT_DIR}/STM32F2xx_HAL_Driver/Inc
    )

file(GLOB STM32_SOURCES ${STM32_LIBRARY_ROOT_DIR}/STM32F2xx_HAL_Driver/Src/*.c)

find_package(PackageHandleStandardArgs)
find_package_handle_standard_args(CMSIS DEFAULT_MSG
        STM32_LIBRARY_ROOT_DIR
        STM32_STARTUP_SOURCE
        STM32_SOURCES
        STM32_INCLUDE_DIRS
        )

