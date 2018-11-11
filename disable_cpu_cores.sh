#!/bin/bash
for ((i = $1; i <= $2; i++)); 
do
	let j=i+8;       	
	echo 0 > /sys/devices/system/cpu/cpu$i/online 
	echo 0 > /sys/devices/system/cpu/cpu$j/online 

	echo "CPU $i Status: " && cat /sys/devices/system/cpu/cpu$i/online
	echo "CPU $j Status: " && cat /sys/devices/system/cpu/cpu$j/online
done
