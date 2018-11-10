# hpc
Scripts for modifying GPU/CPU


How to run:
1. Firewalls must be disabled, so run the following commands to do this.
  a. sudo systemctl stop firewalld.service
  b. sudo systemctl disable firewalld.service
2. The nodes that you want to change the GPU clocks on must have the following files in the same location
  a. clocks
  b. update_GPU_Clocks.sh
3. The control node needs to have talker
4. Run ./clocks on the remote nodes
5. Run ./talker ipaddr msg on host node
  a. Example command: ./talker galactica s
    i. This would increase the clock speed to the next highest frequency
  b. ./talker galactica w
    i. This would decrease the clock speed to the next lowest frequency


Notes:
1. Currently needs to send command to each node seperately

TODO:
1. Link it back with curses to be able to interactively drive the messages by pressing the "w" and "s" instead of running a command each time
2. Send the commands to multiple nodes at the same time
  i. Possibly use a config file at the start to load the ip's?
3. Have the remote PC send a confirmation back that clocks were changed
