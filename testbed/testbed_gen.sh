# First delete if the namespaces exists
sudo ip netns del client
sudo ip netns del server
sudo ip netns del router

# Create the client and server namespace
sudo ip netns add client
sudo ip netns add server

# Create 2 pair of veth devices. Will be used in the above namespace
sudo ip link add ethc type veth peer name ethr1
sudo ip link add eths type veth peer name ethr2

# Add one end of the above veth devices to each of the namespace
sudo ip link set ethc netns client
sudo ip link set eths netns server

# Bring up the veth devices
sudo ip netns exec client ip link set ethc up
sudo ip netns exec server ip link set eths up

# Add IP address to the devices
sudo ip netns exec client ip address add 10.0.0.1/24 dev ethc
sudo ip netns exec server ip address add 10.0.2.1/24 dev eths

# Create the router namespace
sudo ip netns add router

# Add the other ends of the veth pair to the router NS
sudo ip link set ethr1 netns router
sudo ip link set ethr2 netns router

# Bring up the veth ends in the router
sudo ip netns exec router ip link set ethr1 up
sudo ip netns exec router ip link set ethr2 up

# Add IP addresses to the router link devices
sudo ip netns exec router ip address add 10.0.0.2/24 dev ethr1
sudo ip netns exec router ip address add 10.0.2.2/24 dev ethr2

# Bring up the loopback interface in all the namespaces
sudo ip netns exec router ip link set lo up
sudo ip netns exec client ip link set lo up
sudo ip netns exec server ip link set lo up

# Add routes in the client and server
sudo ip netns exec client ip route add default via 10.0.0.2 dev ethc
sudo ip netns exec server ip route add default via 10.0.2.2 dev eths

# Enable forwarding
sudo ip netns exec router sysctl -w net.ipv4.ip_forward=1

# Uncomment to test ping
# sudo ip netns exec client ping 10.0.2.1