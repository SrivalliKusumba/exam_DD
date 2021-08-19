obj-m:= Q2.o

KERNELDIR = /lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

dafault:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	gcc -o app_write app_write.c
	gcc -o app_read app_read.c
	gcc -o app_ioctl app_ioctl.c

install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm app_write
	rm app_read
	rm app_ioctl

