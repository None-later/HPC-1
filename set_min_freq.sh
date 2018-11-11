#!/bin/bash

freq=2800000

for i in {0..31} 
do 
	echo "$freq" > /sys/devices/system/cpu/cpu$i/cpufreq/scaling_min_freq
done
