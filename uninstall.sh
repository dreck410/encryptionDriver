#!/bin/bash
#sudo apt-get install linux-headers-generic-pae
sudo rmmod $1.ko
sudo chmod 666 /dev/$1
sudo mknod /dev/$1 c 60 0

