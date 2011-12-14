# Invoked from kernel build system
ifneq ($(KERNELRELEASE),)
	obj-m := scull.o
# Otherwise
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

.PHONY: clean

clean:
	rm -rf *.o *.~ *.ko *.mo.c *.order *.symvers
