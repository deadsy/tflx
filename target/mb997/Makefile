TOP = ../..
include $(TOP)/mk/common.mk

OUTPUT = tflx

HAL_DIR = $(TOP)/ext/cube/Drivers/STM32F4xx_HAL_Driver
CMSIS_DIR = $(TOP)/ext/cube/Drivers/CMSIS
CMSIS_STM32F4_DIR = $(CMSIS_DIR)/Device/ST/STM32F4xx

SRC += $(HAL_DIR)/Src/stm32f4xx_hal.c \
	$(HAL_DIR)/Src/stm32f4xx_hal_rcc.c \
	$(HAL_DIR)/Src/stm32f4xx_hal_rcc_ex.c \
	$(HAL_DIR)/Src/stm32f4xx_hal_cortex.c \
	$(HAL_DIR)/Src/stm32f4xx_hal_gpio.c \
	$(CMSIS_STM32F4_DIR)/Source/Templates/system_stm32f4xx.c \

# soc library sources
LIB_DIR = $(TOP)/soc/st/stm32f4/lib
SRC += $(LIB_DIR)/gpio.c \
	$(LIB_DIR)/delay.c \
	$(LIB_DIR)/usart.c \

#	$(LIB_DIR)/pwm.c \
# $(LIB_DIR)/i2c.c \
#	$(LIB_DIR)/i2s.c \
#	$(LIB_DIR)/dma.c \
#	$(LIB_DIR)/adc.c \
#	$(LIB_DIR)/rng.c \
#	$(LIB_DIR)/spi.c \

# target sources
TARGET_DIR = $(TOP)/target/mb997
SRC += $(TARGET_DIR)/main.c \

# common
COMMON_DIR = $(TOP)/common
SRC += $(COMMON_DIR)/logging.c \
	$(COMMON_DIR)/debounce.c \
	$(COMMON_DIR)/rtt/SEGGER_RTT.c \
	$(COMMON_DIR)/rtt/SEGGER_RTT_printf.c \

#	$(COMMON_DIR)/syscalls.c \
#	$(COMMON_DIR)/rand.c \

OBJ = $(patsubst %.c, %.o, $(SRC))
OBJ += $(TARGET_DIR)/start.o

# include paths
INCLUDE += -I$(TOP)/soc/st/stm32f4/lib
INCLUDE += -I$(HAL_DIR)/Inc
INCLUDE += -I$(CMSIS_DIR)/Include
INCLUDE += -I$(CMSIS_STM32F4_DIR)/Include
INCLUDE += -I$(TARGET_DIR)
INCLUDE += -I$(COMMON_DIR)
INCLUDE += -I$(COMMON_DIR)/rtt

# defines
DEFINE = -DSTM32F407xx
DEFINE += -DSTDIO_SERIAL

# linker flags
LDSCRIPT = stm32f407vg_flash.ld
X_LDFLAGS = -T$(LDSCRIPT) -Wl,-Map,$(OUTPUT).map -Wl,--gc-sections

.S.o:
	$(X_GCC) $(INCLUDE) $(DEFINE) $(X_CFLAGS) -c $< -o $@
.c.o:
	$(X_GCC) $(INCLUDE) $(DEFINE) $(X_CFLAGS) -c $< -o $@

.PHONY: all clean

all: $(OBJ)
	$(X_GCC) $(X_CFLAGS) $(X_LDFLAGS) $(OBJ) -o $(OUTPUT)
	$(X_OBJCOPY) -O binary $(OUTPUT) $(OUTPUT).bin

clean:
	-rm $(OBJ)	
	-rm $(OUTPUT)
	-rm $(OUTPUT).map	
	-rm $(OUTPUT).bin	
