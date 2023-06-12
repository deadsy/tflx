#------------------------------------------------------------------------------
# Makefile to get and build external dependencies.

TOP = ..

CURRENT_DIR = $(shell pwd)
DL_DIR = $(TOP)/dl
USR_DIR = $(CURRENT_DIR)/usr
FILES_DIR = $(CURRENT_DIR)/files
TOOLCHAIN = $(CURRENT_DIR)/../mk/toolchain_arm_cm4.cmake

.PHONY: all
all: .stamp_gcc .stamp_cube .stamp_tfl

.PHONY: clean
clean:
	-rm -rf $(USR_DIR)
	-rm -rf $(GCC_DIR)
	-rm -rf $(CMSIS_DIR)
	-rm -rf $(NN_DIR)
	-rm -rf $(TFL_DIR)
	-rm -rf $(CUBE_DIR)
	-rm -rf $(FB_DIR)
	-rm -rf $(GML_DIR)
	-rm -rf $(RUY_DIR)
	-rm .stamp_*

#------------------------------------------------------------------------------
# ruy matrix multiplication library
# https://github.com/google/ruy

# ruy library
RUY_VER = d371283
RUY_URL = https://github.com/google/ruy/tarball/$(RUY_VER)
RUY_FILE = ruy-$(RUY_VER).tar.gz
RUY_TGZ = $(DL_DIR)/$(RUY_FILE)
RUY_DIR = $(TOP)/ext/ruy
RUY_BUILD = $(RUY_DIR)/build

$(RUY_TGZ):
	mkdir -p $(RUY_DIR)
	wget $(RUY_URL) -O $(RUY_TGZ)

.stamp_ruy: $(RUY_TGZ)
	mkdir -p $(RUY_DIR)
	tar -C $(RUY_DIR) -zxf $(RUY_TGZ) --strip-components 1
	touch $@

#------------------------------------------------------------------------------
# gemmlowp library
# https://github.com/google/gemmlowp

GML_VER = 719139c
GML_URL = https://github.com/google/gemmlowp/tarball/$(GML_VER)
GML_FILE = gemmlowp-$(GML_VER).tar.gz
GML_TGZ = $(DL_DIR)/$(GML_FILE)
GML_DIR = $(TOP)/ext/gemmlowp

$(GML_TGZ):
	mkdir -p $(DL_DIR)
	wget $(GML_URL) -O $(GML_TGZ)

.stamp_gemmlowp: $(GML_TGZ)
	mkdir -p $(GML_DIR)
	tar -C $(GML_DIR) -zxf $(GML_TGZ) --strip-components 1
	mkdir -p $(USR_DIR)/include
	cp -r $(GML_DIR)/fixedpoint $(USR_DIR)/include
	cp -r $(GML_DIR)/internal $(USR_DIR)/include
	touch $@

#------------------------------------------------------------------------------
# gcc build tools for ARM

GCC_VER = 12.2.mpacbti-rel1
GCC_URL = https://developer.arm.com/-/media/Files/downloads/gnu/$(GCC_VER)/binrel/arm-gnu-toolchain-$(GCC_VER)-x86_64-arm-none-eabi.tar.xz
GCC_FILE = arm-gnu-toolchain-$(GCC_VER)-x86_64-arm-none-eabi.tar.xz
GCC_TXZ = $(DL_DIR)/$(GCC_FILE)
GCC_DIR = $(TOP)/ext/gcc

$(GCC_TXZ):
	mkdir -p $(DL_DIR)
	wget $(GCC_URL) -O $(GCC_TXZ)

.stamp_gcc: $(GCC_TXZ)
	mkdir -p $(GCC_DIR)
	tar -C $(GCC_DIR) -Jxf $(GCC_TXZ) --strip-components 1
	touch $@

#------------------------------------------------------------------------------
# flatbuffers library
# https://github.com/google/flatbuffers

FB_VER = a66de58
FB_URL = https://github.com/google/flatbuffers/tarball/$(FB_VER)
FB_FILE = flatbuffers-$(FB_VER).tar.gz
FB_TGZ = $(DL_DIR)/$(FB_FILE)
FB_DIR = $(TOP)/ext/flatbuffers
FB_BUILD = $(FB_DIR)/build

$(FB_TGZ):
	mkdir -p $(DL_DIR)
	wget $(FB_URL) -O $(FB_TGZ)

.stamp_flatbuffers: $(FB_TGZ) .stamp_gcc
	mkdir -p $(FB_DIR)
	tar -C $(FB_DIR) -zxf $(FB_TGZ) --strip-components 1
	patch -b -p1 < ./patches/100-flatbuffers.patch
	cmake -GNinja \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) \
		-DCMAKE_INSTALL_PREFIX=$(USR_DIR) \
		-DFLATBUFFERS_BUILD_TESTS=OFF \
		-DFLATBUFFERS_BUILD_FLATC=OFF \
		-DFLATBUFFERS_BUILD_FLATHASH=OFF \
		-S $(FB_DIR) -B $(FB_BUILD)
	ninja -C $(FB_BUILD) install
	touch $@

#------------------------------------------------------------------------------
# ARM CMSIS Library
# https://github.com/ARM-software/CMSIS_5

CMSIS_VER = dde5bac
CMSIS_URL = https://github.com/ARM-software/CMSIS_5/tarball/$(CMSIS_VER)
CMSIS_FILE = cmsis-$(CMSIS_VER).tar.gz
CMSIS_TGZ = $(DL_DIR)/$(CMSIS_FILE)
CMSIS_DIR = $(TOP)/ext/cmsis

$(CMSIS_TGZ):
	mkdir -p $(DL_DIR)
	wget $(CMSIS_URL) -O $(CMSIS_TGZ)

.stamp_cmsis: $(CMSIS_TGZ)
	mkdir -p $(CMSIS_DIR)
	tar -C $(CMSIS_DIR) -zxf $(CMSIS_TGZ) --strip-components 1
	touch $@

#------------------------------------------------------------------------------
# ARM CMSIS Neural Network Library
# https://github.com/ARM-software/CMSIS-NN

NN_VER = d071e9f
NN_URL = https://github.com/ARM-software/CMSIS-NN/tarball/$(NN_VER)
NN_FILE = cmsis-nn-$(NN_VER).tar.gz
NN_TGZ = $(DL_DIR)/$(NN_FILE)
NN_DIR = $(TOP)/ext/cmsis-nn
NN_BUILD = $(NN_DIR)/build

$(NN_TGZ):
	mkdir -p $(DL_DIR)
	wget $(NN_URL) -O $(NN_TGZ)

.stamp_nn: $(NN_TGZ) .stamp_gcc
	mkdir -p $(NN_DIR)
	tar -C $(NN_DIR) -zxf $(NN_TGZ) --strip-components 1
	mkdir -p $(NN_BUILD)
	cp ./patches/arm-none-eabi-gcc.cmake $(NN_BUILD)
	cmake -GNinja \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) \
		-S $(NN_DIR) -B $(NN_BUILD)
	ninja -C $(NN_BUILD)
	mkdir -p $(USR_DIR)/lib
	cp $(NN_BUILD)/libcmsis-nn.a $(USR_DIR)/lib
	touch $@

#------------------------------------------------------------------------------
# tensorflow lite for micros library
# https://github.com/tensorflow/tflite-micro

# tensorflow lite
TFL_VER = 78b4040
TFL_URL = https://github.com/tensorflow/tflite-micro/tarball/$(TFL_VER)
TFL_FILE = tfl-$(TFL_VER).tar.gz
TFL_TGZ = $(DL_DIR)/$(TFL_FILE)
TFL_DIR = $(TOP)/ext/tfl
TFL_BUILD = $(TFL_DIR)/build

$(TFL_TGZ):
	mkdir -p $(DL_DIR)
	wget $(TFL_URL) -O $(TFL_TGZ)

.stamp_tfl: $(TFL_TGZ) .stamp_gcc .stamp_flatbuffers .stamp_gemmlowp .stamp_ruy
	mkdir -p $(TFL_DIR)
	tar -C $(TFL_DIR) -zxf $(TFL_TGZ) --strip-components 1
	cp -r files/tfl/* $(TFL_DIR)
	cmake -GNinja \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) \
		-S $(TFL_DIR) -B $(TFL_BUILD)
	ninja -C $(TFL_BUILD)
	mkdir -p $(USR_DIR)/lib
	cp $(TFL_BUILD)/libtfl.a $(USR_DIR)/lib
	touch $@

#------------------------------------------------------------------------------
# stm32f4 cube sdk
# https://github.com/STMicroelectronics/STM32CubeF4

CUBE_VER = 1.27.1
CUBE_URL = https://github.com/STMicroelectronics/STM32CubeF4/archive/refs/tags/v$(CUBE_VER).tar.gz
CUBE_FILE = cube-$(CUBE_VER).tar.gz
CUBE_TGZ = $(DL_DIR)/$(CUBE_FILE)
CUBE_DIR = $(TOP)/ext/cube

$(CUBE_TGZ):
	mkdir -p $(DL_DIR)
	wget $(CUBE_URL) -O $(CUBE_TGZ)

.stamp_cube: $(CUBE_TGZ)
	mkdir -p $(CUBE_DIR)
	tar -C $(CUBE_DIR) -zxf $(CUBE_TGZ) --strip-components 1
	touch $@

#------------------------------------------------------------------------------
