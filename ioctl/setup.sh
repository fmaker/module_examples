#!/bin/bash
if [ -a /dev/ioctl ]
then
	rm /dev/ioctl
fi
rmmod ioctl
insmod ./ioctl.ko
mknod /dev/ioctl c 300 0
