TOP = ..

CURRENT_DIR = $(shell pwd)
DL_DIR = $(TOP)/dl
USR_DIR = $(CURRENT_DIR)/usr

# gcc tools
GCC_VER = 12.2.mpacbti-rel1
GCC_URL = https://developer.arm.com/-/media/Files/downloads/gnu/$(GCC_VER)/binrel/arm-gnu-toolchain-$(GCC_VER)-x86_64-arm-none-eabi.tar.xz
GCC_FILE = arm-gnu-toolchain-$(GCC_VER)-x86_64-arm-none-eabi.tar.xz
GCC_TXZ = $(DL_DIR)/$(GCC_FILE)
GCC_DIR = $(TOP)/ext/gcc

# cmsis
CMSIS_VER = dde5bac
CMSIS_URL = https://github.com/ARM-software/CMSIS_5/tarball/$(CMSIS_VER)
CMSIS_FILE = cmsis-$(CMSIS_VER).tar.gz
CMSIS_TGZ = $(DL_DIR)/$(CMSIS_FILE)
CMSIS_DIR = $(TOP)/ext/cmsis

# cmsis-nn
NN_VER = d071e9f
NN_URL = https://github.com/ARM-software/CMSIS-NN/tarball/$(NN_VER)
NN_FILE = cmsis-nn-$(NN_VER).tar.gz
NN_TGZ = $(DL_DIR)/$(NN_FILE)
NN_DIR = $(TOP)/ext/cmsis-nn

# tensorflow lite
TFL_VER = 78b4040
TFL_URL = https://github.com/tensorflow/tflite-micro/tarball/$(TFL_VER)
TFL_FILE = tfl-$(TFL_VER).tar.gz
TFL_TGZ = $(DL_DIR)/$(TFL_FILE)
TFL_DIR = $(TOP)/ext/tfl

.PHONY: all
all: .stamp_gcc .stamp_cmsis .stamp_nn .stamp_tfl

.PHONY: clean
clean:
	-rm -rf $(USR_DIR)
	-rm -rf $(GCC_DIR)
	-rm -rf $(CMSIS_DIR)
	-rm -rf $(NN_DIR)
	-rm -rf $(TFL_DIR)
	-rm .stamp_*

$(GCC_TXZ):
	mkdir -p $(DL_DIR)
	wget $(GCC_URL) -O $(GCC_TXZ)

$(CMSIS_TGZ):
	mkdir -p $(DL_DIR)
	wget $(CMSIS_URL) -O $(CMSIS_TGZ)

$(NN_TGZ):
	mkdir -p $(DL_DIR)
	wget $(NN_URL) -O $(NN_TGZ)

$(TFL_TGZ):
	mkdir -p $(DL_DIR)
	wget $(TFL_URL) -O $(TFL_TGZ)

.stamp_gcc: $(GCC_TXZ)
	mkdir -p $(GCC_DIR)
	tar -C $(GCC_DIR) -Jxf $(GCC_TXZ) --strip-components 1
	touch $@

.stamp_cmsis: $(CMSIS_TGZ)
	mkdir -p $(CMSIS_DIR)
	tar -C $(CMSIS_DIR) -zxf $(CMSIS_TGZ) --strip-components 1
	touch $@

.stamp_nn: $(NN_TGZ)
	mkdir -p $(NN_DIR)
	tar -C $(NN_DIR) -zxf $(NN_TGZ) --strip-components 1
	touch $@

.stamp_tfl: $(TFL_TGZ)
	mkdir -p $(TFL_DIR)
	tar -C $(TFL_DIR) -zxf $(TFL_TGZ) --strip-components 1
	touch $@

 
