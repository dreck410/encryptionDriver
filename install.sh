#!/bin/bash
#sudo apt-get install linux-headers-generic-pae
make
sudo insmod $1.ko
sudo mknod /dev/$1 c 60 0
sudo chmod 666 /dev/$1
