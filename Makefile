
.PHONY: all
all: .stamp_ext

.PHONY: clean
clean:

.PHONY: clobber
clobber: clean
	make -C ext clean
	-rm .stamp_ext

.stamp_ext:
	make -C ext all
	touch $@
