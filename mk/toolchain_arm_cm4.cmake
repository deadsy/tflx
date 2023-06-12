# CMAKE_TOOLCHAIN_FILE for ARM-Cortex-M4 cross compilation

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Without that flag CMake is not able to pass test compilation check
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOP ${CMAKE_SOURCE_DIR}/../..)
set(GCC_PREFIX ${TOP}/ext/gcc/bin/arm-none-eabi-)

set(CMAKE_C_COMPILER ${GCC_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${GCC_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${GCC_PREFIX}gcc)
set(CMAKE_C_OBJCOPY ${GCC_PREFIX}objcopy)
set(CMAKE_LINKER ${GCC_PREFIX}ld)
set(CMAKE_AR ${GCC_PREFIX}ar)
set(CMAKE_RANLIB ${GCC_PREFIX}ranlib)
set(CMAKE_SIZE ${GCC_PREFIX}size)
set(CMAKE_STRIP ${GCC_PREFIX}strip)

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

string(JOIN " " CM4_C_FLAGS
	${COMMON_FLAGS}
	"-Wstrict-prototypes" # require strict prototypes
	"-std=c11" # ISO/IEC 9899:2011 C standard
)

string(JOIN " " CM4_CXX_FLAGS
	${COMMON_FLAGS}
	"-std=c++11" # ISO/IEC 14882:2011 C++ standard
	"-fno-rtti" # no runtime type information
	"-fno-exceptions" # no exception code
	"-fno-threadsafe-statics" # don't emit thread safe code for local statics
)

set(CMAKE_ASM_FLAGS ${CM4_C_FLAGS} CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS ${CM4_C_FLAGS} CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS ${CM4_CXX_FLAGS} CACHE STRING "" FORCE)

#set(CMAKE_C_FLAGS_DEBUG         <c_flags_for_debug>)
#set(CMAKE_C_FLAGS_RELEASE       <c_flags_for_release>)
#set(CMAKE_CXX_FLAGS_DEBUG       <cpp_flags_for_debug>)
#set(CMAKE_CXX_FLAGS_RELEASE     <cpp_flags_for_release>)
#set(CMAKE_EXE_LINKER_FLAGS      <linker_flags>)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
