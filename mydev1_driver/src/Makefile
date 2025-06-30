KERNEL_DIR = /ib/modules/$(shell umname -r)/build
PWD := $(CURDIR)

obj-m := mydev1_driver.o

EXTRA_CFLAGS += -I../modules/

all:
	make -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean
