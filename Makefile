TOP = .

include $(TOP)/mk/common.mk

TARGET ?= mb997

TARGET_DIR = $(TOP)/target/$(TARGET)
BIN_FILE = $(TARGET_DIR)/tflx.bin

.PHONY: all
all: .stamp_ext
	make -C $(TARGET_DIR) $@

.PHONY: program
program: 
	st-flash write $(BIN_FILE) 0x08000000

.PHONY: clean
clean:
	make -C $(TARGET_DIR) $@

# clean + remove the 3rd party libraries
.PHONY: clobber
clobber: clean
	$(MAKE) -C ext clean
	-rm .stamp_ext

# build 3rd party libraries
.stamp_ext:
	$(MAKE) -C ext
	touch $@
