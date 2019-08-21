KDIR := /lib/modules/$(shell uname -r)/build

obj-m += netlinkKernel.o

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	gcc send.c -o send
	gcc recv.c -o recv

clean:
	rm -rf *.o *.ko *.mod.* *.cmd .module* modules* Module* .*.cmd .tmp*
	rm send
	rm recv
	rm netlinkUser
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
