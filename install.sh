#!/bin/bash
#sudo apt-get install linux-headers-generic-pae
make
insmod encrypt.ko
mknod /dev/encrypt c 60 0
chmod 666 /dev/encrypt
gcc rot47.c -o rot47
