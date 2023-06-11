cmake_minimum_required(VERSION 3.22)

project(tflx
	LANGUAGES C CXX ASM
)

set(TOP ${CMAKE_SOURCE_DIR}/../..)
set(GCC_PATH ${TOP}/ext/gcc/bin)

set(HAL_DIR ${TOP}/ext/cube/Drivers/STM32F4xx_HAL_Driver)
set(CMSIS_DIR ${TOP}/ext/cube/Drivers/CMSIS)
set(CMSIS_STM32F4_DIR ${CMSIS_DIR}/Device/ST/STM32F4xx)
set(SOC_DIR ${TOP}/soc/st/stm32f4/lib)
set(COMMON_DIR ${TOP}/common)
set(APP_DIR ${TOP}/app)
set(TFL_DIR ${TOP}/ext/tfl)
set(USR_DIR ${TOP}/ext/usr)

set(CMAKE_C_COMPILER ${GCC_PATH}/arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER ${GCC_PATH}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${GCC_PATH}/arm-none-eabi-g++)
set(CMAKE_C_OBJCOPY ${GCC_PATH}/arm-none-eabi-objcopy)
set(CMAKE_LINKER ${GCC_PATH}/arm-none-eabi-ld)
set(CMAKE_AR ${GCC_PATH}/arm-none-eabi-ar)

string(JOIN " " COMMON_FLAGS
	"-Werror" # warnings are errors
	"-Wall" # all warnings
	"-Wextra" # extra warnings
	"-fno-unwind-tables"
	"-ffunction-sections" # functions in their own section (link with --gc-sections)
	"-fdata-sections" # data objects in their own section (link with --gc-sections)
	"-fmessage-length=0" # single line for message formatting
	"-mthumb" # generate arm thumb code
	"-mlittle-endian" # generate little endan code (required?)
	"-mthumb-interwork" # interwork with non-thumb arm code (required?)
	"-mcpu=cortex-m4" # build for a cortex m4
	"-mfloat-abi=hard" # hardware floating point
	"-mfpu=fpv4-sp-d16" # describe the floating point
	"-funsigned-char" # chars are unsigned
	"-fomit-frame-pointer" # omit stack frame pointer
)

string(JOIN " " CMAKE_C_FLAGS
	${COMMON_FLAGS}
	"-Wstrict-prototypes" # require strict prototypes
	"-std=c11" # ISO/IEC 9899:2011 C standard
)

string(JOIN " " CMAKE_CXX_FLAGS
	${COMMON_FLAGS}
	"-std=c++11" # ISO/IEC 14882:2011 C++ standard
	"-fno-rtti" # no runtime type information
	"-fno-exceptions" # no exception code
	"-fno-threadsafe-statics" # don't emit thread safe code for local statics
	"-Wno-unused-parameter"
)

set(CMAKE_ASM_FLAGS ${CMAKE_C_FLAGS})

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
	#${APP_DIR}/debug_log.cc
  #${APP_DIR}/micro_time.cc
  #${APP_DIR}/system_setup.cc
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
	"-Wl,-Map,${PROJECT_NAME}.map"
	"-Wl,--gc-sections"
)

add_custom_target(${PROJECT_NAME}.bin ALL DEPENDS ${PROJECT_NAME}.elf)
add_custom_command(TARGET ${PROJECT_NAME}.bin COMMAND ${CMAKE_C_OBJCOPY} ARGS -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin)
