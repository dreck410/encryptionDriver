#!/bin/bash
#sudo apt-get install linux-headers-generic-pae
make
sudo insmod encrypt.ko
sudo mknod /dev/encrypt c 60 0
sudo chmod 666 /dev/encrypt
