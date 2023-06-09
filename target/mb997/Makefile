TOP = ../..
include $(TOP)/mk/common.mk

OUTPUT = tflx

HAL_DIR = $(TOP)/ext/cube/Drivers/STM32F4xx_HAL_Driver
CMSIS_DIR = $(TOP)/ext/cube/Drivers/CMSIS
CMSIS_STM32F4_DIR = $(CMSIS_DIR)/Device/ST/STM32F4xx
TENSORFLOW_DIR = $(TOP)/ext/tfl/build
USR_DIR = $(TOP)/ext/usr

C_SRC += $(HAL_DIR)/Src/stm32f4xx_hal.c \
	$(HAL_DIR)/Src/stm32f4xx_hal_rcc.c \
	$(HAL_DIR)/Src/stm32f4xx_hal_rcc_ex.c \
	$(HAL_DIR)/Src/stm32f4xx_hal_cortex.c \
	$(HAL_DIR)/Src/stm32f4xx_hal_gpio.c \
	$(CMSIS_STM32F4_DIR)/Source/Templates/system_stm32f4xx.c \

# soc library sources
LIB_DIR = $(TOP)/soc/st/stm32f4/lib
C_SRC += $(LIB_DIR)/gpio.c \
	$(LIB_DIR)/delay.c \
	$(LIB_DIR)/usart.c \

#$(LIB_DIR)/pwm.c \
#$(LIB_DIR)/i2c.c \
#$(LIB_DIR)/i2s.c \
#$(LIB_DIR)/dma.c \
#$(LIB_DIR)/adc.c \
#$(LIB_DIR)/rng.c \
#$(LIB_DIR)/spi.c \

# target sources
TARGET_DIR = $(TOP)/target/mb997
C_SRC += $(TARGET_DIR)/main.c \

# common
COMMON_DIR = $(TOP)/common
C_SRC += $(COMMON_DIR)/logging.c \
	$(COMMON_DIR)/debounce.c \
	$(COMMON_DIR)/rtt/SEGGER_RTT.c \
	$(COMMON_DIR)/rtt/SEGGER_RTT_printf.c \
	$(COMMON_DIR)/syscalls.c \

#	$(COMMON_DIR)/rand.c \

# application
APP_DIR = $(TOP)/app
CXX_SRC += $(APP_DIR)/tfl_main.cc \
	$(APP_DIR)/hello_world_float_model_data.cc \
	$(APP_DIR)/hello_world_int8_model_data.cc \


OBJ = $(patsubst %.c, %.o, $(C_SRC))
OBJ += $(patsubst %.cc, %.o, $(CXX_SRC))
OBJ += $(TARGET_DIR)/start.o

# include paths
INCLUDE += -I$(TOP)/soc/st/stm32f4/lib
INCLUDE += -I$(HAL_DIR)/Inc
INCLUDE += -I$(CMSIS_DIR)/Include
INCLUDE += -I$(CMSIS_STM32F4_DIR)/Include
INCLUDE += -I$(TARGET_DIR)
INCLUDE += -I$(COMMON_DIR)
INCLUDE += -I$(COMMON_DIR)/rtt
INCLUDE += -I$(TENSORFLOW_DIR)
INCLUDE += -I$(TENSORFLOW_DIR)/third_party/flatbuffers/include
INCLUDE += -I$(TENSORFLOW_DIR)/third_party/gemmlowp

# defines
DEFINE = -DSTM32F407xx
DEFINE += -DSTDIO_SERIAL

# linker flags
LDSCRIPT = stm32f407vg_flash.ld
LDFLAGS = -T$(LDSCRIPT) -Wl,-Map,$(OUTPUT).map -Wl,--gc-sections

LIB_PATH += -L$(USR_DIR)/lib
LIB += -ltflm
LIB += -lcmsis-nn
LIB += -lstdc++

DEFINE += -DTF_LITE_STATIC_MEMORY
DEFINE += -DTF_LITE_MCU_DEBUG_LOG
DEFINE += -DPROJECT_GENERATION
DEFINE += -DCMSIS_NN

CXXFLAGS += -Wno-unused-parameter # tensor flow lite has some unused parameters

.S.o:
	$(CC) $(INCLUDE) $(DEFINE) $(CFLAGS) -c $< -o $@
.c.o:
	$(CC) $(INCLUDE) $(DEFINE) $(CFLAGS) -c $< -o $@
.cc.o:
	$(CXX) $(INCLUDE) $(DEFINE) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean

all: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIB_PATH) $(LIB) -o $(OUTPUT)
	$(OBJCOPY) -O binary $(OUTPUT) $(OUTPUT).bin

clean:
	-rm $(OBJ)	
	-rm $(OUTPUT)
	-rm $(OUTPUT).map	
	-rm $(OUTPUT).bin	
