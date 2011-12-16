# Invoked from kernel build system
ifneq ($(KERNELRELEASE),)
	obj-m := moddep_ex.o moddep_ex2.o
# Otherwise
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

.PHONY: clean

clean:
	rm -rf *.o *.~ *.ko *.mo.c *.order *.symvers *.mod.c
