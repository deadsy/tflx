
set(TOP ${CMAKE_SOURCE_DIR}/../..)
set(GCC_PATH ${TOP}/ext/gcc/bin)

set(CMAKE_C_COMPILER ${GCC_PATH}/arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER ${GCC_PATH}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${GCC_PATH}/arm-none-eabi-g++)
set(CMAKE_C_OBJCOPY ${GCC_PATH}/arm-none-eabi-objcopy)
set(CMAKE_LINKER ${GCC_PATH}/arm-none-eabi-ld)
set(CMAKE_AR ${GCC_PATH}/arm-none-eabi-ar)

# Without that flag CMake is not able to pass test compilation check
if (${CMAKE_VERSION} VERSION_EQUAL "3.6.0" OR ${CMAKE_VERSION} VERSION_GREATER "3.6")
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
else ()
    set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nosys.specs")
endif ()

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
  "-Wno-psabi"
	"-std=c++11" # ISO/IEC 14882:2011 C++ standard
	"-fno-rtti" # no runtime type information
	"-fno-exceptions" # no exception code
	"-fno-threadsafe-statics" # don't emit thread safe code for local statics
)

set(CMAKE_ASM_FLAGS ${CMAKE_C_FLAGS})
