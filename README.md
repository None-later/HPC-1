# hpc
Scripts for interactively changing GPU frequency

How to run: <br/>
1. Run sudo ./clocks on the remote nodes to listen for signals from the host node <br/>
i. -v enables verbose mode. By default there is no output <br/>
ii. sudo required for disabling firewalls and running nvidia-smi <br/>
2. Run ./talker <ips> on the host node <br/>
a. Example: ./talker pegasus galactica <br/>
b. Can send commands to as many nodes as possible <br/>
c. w increases frequency speed <br/>
d. s decreases frequency speed <br/>
i. There is bounds checking for the speeds <br/>
e. q to quit <br/>

Notes: <br/>
TODO: <br/>
1. Have the remote PC send a confirmation back that clocks were changed <br/>


