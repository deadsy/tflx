cmake_minimum_required(VERSION 3.22)
project(tflx)

#set(CMAKE_SYSTEM_NAME Generic)
#set(CMAKE_SYSTEM_PROCESSOR arm)
#set(CMAKE_CROSSCOMPILING 1)

set(TOP ${CMAKE_SOURCE_DIR}/../..)
set(GCC_PATH ${TOP}/ext/gcc/bin)

set(HAL_DIR ${TOP}/ext/cube/Drivers/STM32F4xx_HAL_Driver)
set(CMSIS_DIR ${TOP}/ext/cube/Drivers/CMSIS)
set(CMSIS_STM32F4_DIR ${CMSIS_DIR}/Device/ST/STM32F4xx)
set(SOC_DIR ${TOP}/soc/st/stm32f4/lib)
set(COMMON_DIR ${TOP}/common)


set(CMAKE_C_COMPILER ${GCC_PATH}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${GCC_PATH}/arm-none-eabi-g++)
set(CMAKE_C_OBJCOPY ${GCC_PATH}/arm-none-eabi-objcopy)
set(CMAKE_LINKER ${GCC_PATH}/arm-none-eabi-ld)
set(CMAKE_AR ${GCC_PATH}/arm-none-eabi-ar)

string(JOIN " " COMMON_FLAGS
	"-Werror"
	"-Wall"
	"-Wextra"
	"-fno-unwind-tables"
	"-ffunction-sections"
	"-fdata-sections"
	"-fmessage-length=0"
	"-mthumb"
	"-mlittle-endian"
	"-mthumb-interwork"
	"-mcpu=cortex-m4"
	"-mfloat-abi=hard"
	"-mfpu=fpv4-sp-d16"
	"-funsigned-char"
	"-fomit-frame-pointer"
)

string(JOIN " " CMAKE_C_FLAGS
	${COMMON_FLAGS}
	"-Wstrict-prototypes"
	"-std=c11"
)


add_executable(${PROJECT_NAME}.elf
	main.c

	${HAL_DIR}/Src/stm32f4xx_hal.c
	${HAL_DIR}/Src/stm32f4xx_hal_rcc.c
	${HAL_DIR}/Src/stm32f4xx_hal_rcc_ex.c
	${HAL_DIR}/Src/stm32f4xx_hal_cortex.c
	${HAL_DIR}/Src/stm32f4xx_hal_gpio.c
	${CMSIS_STM32F4_DIR}/Source/Templates/system_stm32f4xx.c

	${SOC_DIR}/gpio.c
	${SOC_DIR}/delay.c
	${SOC_DIR}/usart.c

	${COMMON_DIR}/logging.c
	${COMMON_DIR}/debounce.c
	${COMMON_DIR}/rtt/SEGGER_RTT.c
	${COMMON_DIR}/rtt/SEGGER_RTT_printf.c
	${COMMON_DIR}/syscalls.c
)


target_include_directories(${PROJECT_NAME}.elf PUBLIC
	${CMAKE_SOURCE_DIR}
	${SOC_DIR}
	${HAL_DIR}/Inc
	${CMSIS_STM32F4_DIR}/Include
	${CMSIS_DIR}/Include
	${TOP}/common/rtt
	${COMMON_DIR}
)

target_compile_definitions(${PROJECT_NAME}.elf PUBLIC
	STM32F407xx
	STDIO_SERIAL
)

add_custom_target(${PROJECT_NAME}.bin ALL DEPENDS ${PROJECT_NAME}.elf)
add_custom_command(TARGET ${PROJECT_NAME}.bin COMMAND ${CMAKE_C_OBJCOPY} ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
