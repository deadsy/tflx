cmake_minimum_required(VERSION 3.21)

project(tflx
	LANGUAGES C CXX ASM
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

set(TOP ${CMAKE_SOURCE_DIR}/../..)

set(HAL_DIR ${TOP}/ext/cube/Drivers/STM32F4xx_HAL_Driver)
set(CMSIS_DIR ${TOP}/ext/cube/Drivers/CMSIS)
set(CMSIS_STM32F4_DIR ${CMSIS_DIR}/Device/ST/STM32F4xx)
set(SOC_DIR ${TOP}/soc/st/stm32f4/lib)
set(COMMON_DIR ${TOP}/common)
set(APP_DIR ${TOP}/app)
set(TFL_DIR ${TOP}/ext/tfl)
set(USR_DIR ${TOP}/ext/usr)

add_executable(${PROJECT_NAME}.elf
	start.S
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

	${APP_DIR}/hello_world_float_model_data.cc
	${APP_DIR}/hello_world_int8_model_data.cc
	${APP_DIR}/tfl_main.cc
)

target_include_directories(${PROJECT_NAME}.elf PUBLIC
	${CMAKE_SOURCE_DIR}
	${SOC_DIR}
	${HAL_DIR}/Inc
	${CMSIS_STM32F4_DIR}/Include
	${CMSIS_DIR}/Include
	${COMMON_DIR}/rtt
	${COMMON_DIR}
	${TFL_DIR}
	${USR_DIR}/include
)

target_compile_definitions(${PROJECT_NAME}.elf PUBLIC
	STM32F407xx
	STDIO_SERIAL
)

target_link_libraries(${PROJECT_NAME}.elf PUBLIC
	${USR_DIR}/lib/libtfl.a
)

set(LDSCRIPT ${CMAKE_SOURCE_DIR}/stm32f407vg_flash.ld)

target_link_options(${PROJECT_NAME}.elf PUBLIC
	"-T${LDSCRIPT}"
	"-Wl,-Map,${PROJECT_NAME}.map" # create a map file
	"-Wl,--gc-sections" # remove unused sections
	"-Wl,--no-warn-rwx-segments" # Supress warning: https://github.com/raspberrypi/pico-sdk/issues/1029 
)

add_custom_target(${PROJECT_NAME}.bin ALL DEPENDS ${PROJECT_NAME}.elf)
add_custom_command(TARGET ${PROJECT_NAME}.bin COMMAND ${CMAKE_C_OBJCOPY} ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
