# hpc
Scripts for modifying GPU/CPU


How to run:
1. Run sudo ./clocks on the remote machines to listen for signals from the host pc
	i. -v enables verbose mode. By default there is no output
	ii. sudo required for disabling firewalls and running nvidia-smi
2. Run ./talker <ips> on the host node
	a. Example: ./talker pegasus galactica
	b. Can send commands to as many nodes as possible
	c. w increases frequency speed 
	d. s decreases frequency speed
		i. There is bounds checking for the speeds
	e. q to quit


Notes:

TODO:
3. Have the remote PC send a confirmation back that clocks were changed
