obj-m = encrypt.o 
KVERSION = /usr/src/linux-headers-3.2.0-35-generic-pae
all:
	$(MAKE) -C $(KVERSION) SUBDIRS=$(PWD) modules
clean:
	make -C /lib/modules/$(KVERSION) M=$(PWD) clean
