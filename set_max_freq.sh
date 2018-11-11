#!/bin/bash

freq=3000000

for i in {0..31} 
do 
	echo "$freq" > /sys/devices/system/cpu/cpu$i/cpufreq/scaling_max_freq
done
