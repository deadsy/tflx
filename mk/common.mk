

# set the version
#X_LIBGCC_DIR = $(XTOOLS_DIR)/lib/gcc/arm-none-eabi/7.2.1/armv7e-m/fpu

# should be ok
#X_LIBC_DIR = $(XTOOLS_DIR)/arm-none-eabi/lib/armv7e-m/fpu

XTOOLS_PATH = $(TOP)/ext/gcc

CC = $(XTOOLS_PATH)/bin/arm-none-eabi-gcc
CXX = $(XTOOLS_PATH)/bin/arm-none-eabi-g++
OBJCOPY = $(XTOOLS_PATH)/bin/arm-none-eabi-objcopy
AR = $(XTOOLS_PATH)/bin/arm-none-eabi-ar
LD = $(XTOOLS_PATH)/bin/arm-none-eabi-ld
GDB = $(XTOOLS_PATH)/bin/arm-none-eabi-gdb

# c/c++ common flags
COMMON_FLAGS += -Werror # warnings are errors
COMMON_FLAGS += -Wall # all warnings
COMMON_FLAGS += -Wextra # extra warnings
COMMON_FLAGS += -fno-unwind-tables
COMMON_FLAGS += -ffunction-sections # functions in their own section (link with --gc-sections)
COMMON_FLAGS += -fdata-sections # data objects in their own section (link with --gc-sections)
COMMON_FLAGS += -fmessage-length=0 # single line for message formatting
COMMON_FLAGS += -mthumb # generate arm thumb code
COMMON_FLAGS += -mlittle-endian # generate little endan code (required?)
COMMON_FLAGS += -mthumb-interwork # interwork with non-thumb arm code (required?)
COMMON_FLAGS += -mcpu=cortex-m4 # build for a cortex m4
COMMON_FLAGS += -mfloat-abi=hard # hardware floating point
COMMON_FLAGS += -mfpu=fpv4-sp-d16 # describe the floating point
COMMON_FLAGS += -funsigned-char # chars are unsigned
COMMON_FLAGS += -fomit-frame-pointer # omit stack frame pointer
#COMMON_FLAGS += -MD # generate a dependency file
 
# c flags
CFLAGS += -Wstrict-prototypes # require strict prototypes
CFLAGS += -std=c11 # ISO/IEC 9899:2011 C standard
CFLAGS += $(COMMON_FLAGS)

# c++ flags (See: https://arobenko.github.io/bare_metal_cpp/)
CXXFLAGS += -std=c++11 # ISO/IEC 14882:2011 C++ standard
CXXFLAGS += -fno-rtti # no runtime type information
CXXFLAGS += -fno-exceptions # no exception code
CXXFLAGS += -fno-threadsafe-statics # don't emit thread safe code for local statics
CXXFLAGS += $(COMMON_FLAGS)

