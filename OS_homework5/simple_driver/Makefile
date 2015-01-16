obj-m := example.o

ifeq ($(KERNELDIR),)
KERNELDIR=/lib/modules/$(shell uname -r)/build
endif

all:
	make -C $(KERNELDIR) M=$(PWD) modules
	sudo insmod example.ko
	sh mkdev.sh 60 0
	gcc test.c -o test

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
	sudo rmmod example
	rm test
	sh rmdev.sh
msg:
	dmesg | grep EXAMPLE

test:
	gcc test.c -o test
