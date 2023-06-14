TOP = .

TARGET ?= mb997

TARGET_DIR = $(TOP)/target/$(TARGET)
BUILD_DIR = $(TARGET_DIR)/build
BIN_FILE = $(BUILD_DIR)/tflx.bin
TOOLCHAIN = $(PWD)/mk/toolchain_arm_cm4.cmake

.PHONY: all
all: .stamp_ext
	mkdir -p $(BUILD_DIR)
	cmake -GNinja \
		-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) \
		-S $(TARGET_DIR) -B $(BUILD_DIR)
	ninja -C $(BUILD_DIR)

.PHONY: program
program: 
	st-flash write $(BIN_FILE) 0x08000000

.PHONY: format
format: 
	./tools/cfmt.py

.PHONY: clean
clean:
	-rm -rf $(BUILD_DIR)

# clean + remove the 3rd party libraries
.PHONY: clobber
clobber: clean
	$(MAKE) -C ext clean
	-rm .stamp_ext

# build 3rd party libraries
.stamp_ext:
	$(MAKE) -C ext
	touch $@
