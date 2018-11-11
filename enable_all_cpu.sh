#!/bin/bash

for i in {1..16} 
do 
	echo 1 > /sys/devices/system/cpu/cpu$i/online 
	echo "CPU $i Status: "; cat /sys/devices/system/cpu/cpu$i/online
done
