KERNEL_DIR := /lib/modules/$(shell uname -r)/build
PWD := $(CURDIR)

obj-m := gpio_module.o
obj-m += led_module.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean