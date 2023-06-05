
# host compilation tools
HOST_GCC = gcc

# cross compilation tools

# set the path
XTOOLS_DIR = $(TOP)/ext/gcc

# set the version
X_LIBGCC_DIR = $(XTOOLS_DIR)/lib/gcc/arm-none-eabi/7.2.1/armv7e-m/fpu

# should be ok
X_LIBC_DIR = $(XTOOLS_DIR)/arm-none-eabi/lib/armv7e-m/fpu
X_GCC = $(XTOOLS_DIR)/bin/arm-none-eabi-gcc
X_GPP = $(XTOOLS_DIR)/bin/arm-none-eabi-g++
X_OBJCOPY = $(XTOOLS_DIR)/bin/arm-none-eabi-objcopy
X_AR = $(XTOOLS_DIR)/bin/arm-none-eabi-ar
X_LD = $(XTOOLS_DIR)/bin/arm-none-eabi-ld
X_GDB = $(XTOOLS_DIR)/bin/arm-none-eabi-gdb

# cross compile flags for cortex m4 build
X_CFLAGS = -Werror -Wall -Wextra -Wstrict-prototypes
X_CFLAGS += -O2
X_CFLAGS += -falign-functions -fomit-frame-pointer -fno-strict-aliasing
X_CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
X_CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
X_CFLAGS += -std=c11

X_CPP_FLAGS = -Werror -Wall -Wextra
X_CPP_FLAGS = -Wno-unused-parameter
X_CPP_FLAGS += -std=c++11
X_CPP_FLAGS +=  -DTF_LITE_STATIC_MEMORY
X_CPP_FLAGS += -fno-unwind-tables
X_CPP_FLAGS += -ffunction-sections
X_CPP_FLAGS += -fdata-sections
X_CPP_FLAGS += -fmessage-length=0
X_CPP_FLAGS += -fno-rtti
X_CPP_FLAGS += -fno-exceptions
X_CPP_FLAGS += -fno-threadsafe-statics
X_CPP_FLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
X_CPP_FLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
