################################################################################
# --- STM32-CodeSourcery-CMake project example ---
# This project is intended as an example/template showing how to use CMake to 
# build C/C++ source code for the STM32 using the CodeSourcery G++ Lite
# toolchain.
#
# Copyright ISORG 2012 (www.isorg.fr)
################################################################################

project(Medula C ASM NONE )
#project(<projectname> NONE)
cmake_minimum_required(VERSION 2.8)

# Turn ON/OFF verbose output
set(CMAKE_VERBOSE_MAKEFILE OFF)

# Add the 'Modules' folder to the search path for FindXXX.cmake files
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

GET_TARGET_PROPERTY(DOC_TARGET doc TYPE)
IF(NOT DOC_TARGET)
  ADD_CUSTOM_TARGET(doc)
ENDIF(NOT DOC_TARGET)


#
# Setup STM32 variables
#
set(STM32_FAMILY "STM32F2xx") 	# Support "STM32F10x", "STM32F2xx", "STM32F4xx"
set(STM32_LIBRARY_ROOT_DIR "Drv" )
include(CMake/STM32.cmake)
set(DRV_DIR "Drv" )
set(LIB_DIR "Lib" )
include(${DRV_DIR}/Drv.cmake)
include(${LIB_DIR}/Lib.cmake)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

include_directories(
    ${CMAKE_SOURCE_DIR}/Inc
    ${STM32_INCLUDE_DIRS}
    ${BSP_INCLUDE_DIRS}
	${DRV_INCLUDE_DIRS}
	${LIB_INCLUDE_DIRS}
    )

#add_definitions(
#    -DUSE_STDPERIPH_DRIVER
#    -DSTM32F4XX
#    )

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSTM32F207xx -DEE_M24LR64 -DUSE_FULL_ASSERT")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_SOURCE_DIR}/Lkr/stm32f207_flash.ld")
#set(CMAKE_EXE_LINKER_FLAGS_INIT  "-T${CMAKE_SOURCE_DIR}/lkr/stm32f407vg_flash.ld")

add_executable(Medula.elf
    Src/main.c
    Src/stm32f2xx_it.c
    Src/stm32f2xx_hal_msp.c
    Src/system_stm32f2xx.c
    Src/Traces.c
    Src/Appli.c
    ${STM32_SOURCES}
    ${STM32_STARTUP_SOURCE}
    ${DRV_SOURCES}
    ${LIB_SOURCES}
    )

target_link_libraries(Medula.elf ${STM32_LIBRARIES})

add_custom_target(Medula.hex DEPENDS Medula.elf COMMAND ${CMAKE_OBJCOPY} -Oihex Medula.elf Medula.hex)
add_custom_target(Medula.bin DEPENDS Medula.elf COMMAND ${CMAKE_OBJCOPY} -Obinary Medula.elf Medula.bin)

# If STM32 ST-Link Utility is found, add a make target to program the chip
if(DEFINED STM32_STLINK_CLI_EXECUTABLE)
    # -c SWD UR : SWD communication protocol, Under Reset
    # -Q : quiet mode, no progress bar
    # -V : Verifies that the programming operation was performed successfully.
    # -P : program file (.hex)
    set(STLINK_CMD ${STM32_STLINK_CLI_EXECUTABLE} -c SWD UR -P ${CMAKE_BINARY_DIR}/Medula.hex)
    add_custom_target(program-flash DEPENDS Medula.hex COMMAND ${STLINK_CMD})
endif()



# add a target to generate Project documentation with Doxygen

  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doc/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doc/Doxyfile @ONLY)
  ADD_CUSTOM_TARGET(doc_Medula
                    doxygen ${CMAKE_CURRENT_BINARY_DIR}/Doc/Doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
  ADD_DEPENDENCIES(doc doc_Medula)

