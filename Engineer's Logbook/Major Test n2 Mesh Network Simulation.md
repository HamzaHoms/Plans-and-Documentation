Aim:
To implement my mesh routing protocol in a simulated environment and observe how it behaves in a full network with an arbitrary number of nodes under different conditions.


Plan:
Each node will be replicable and have internal structures that represents the FIFOs and drivers. The structures will not hold any actual data, only states such as FIFO filling, Packet Data, driver busy intervals, and over-write/error counts.

The simulation itself will be microsecond timestep based. Every timestep it will iterate over each node's structures and update them, based on the states of the node and surrounding nodes.

In the beginning the simulation will procedurally generate a number of nodes with abstract "positions", then based on the positions it will link every node to any nodes within a certain distance of it, the linking is simply adding the index of the linked node to the "linked nodes" buffer of the current node. 

The packets will mainly be taken as SC-to-SC, meaning what matters most is the UART and SX-1268 drivers' delays, as for the timing of the routing logic, that will be a test parameter to figure out how much lee-way I have.


Test Paramters:
1) Routing Logic Interval: How long the router controller can spend doing routing logic on a single packet, the routing logic in matlab can be done in one tick, but there will be a delay until the packet is re-transmitted. will be measured in us/byte.
2) Mesh Propagation Delay: How long a packet takes to propagate from one side of the network to the other side on average, measured by injecting packets on an edge node every interval of time and seeing how long it takes to reach the other side. measured in us/byte and will be averaged over multiple tests.
3) Max Mesh Packet Density: What is the maximum amount of packets flowing through the mesh before it starts congesting. measured in bytes/s.
4) Packet Loss Rate: How often packets drop or do not reach their destination, measured as an average of dropped packets over the entire simulation time. measured as a % of total packets sent throughout the simulation time.


Pre-requisite values needed for test:
1) LoRa Service Time: The time needed for a single packet of n-bytes to be transmitted over LoRa starting from the SX68_Transmit call on RC1 to the SX68_ReadRXPacket Call on RC2. measured in us/byte + 0-byte service time.
2) UART Service Time: The time needed for a single packet of n-bytes to get from SCx to RCx or vice versa. measured in us/byte.

both can be retrieved from the data I have from [[Major Test n1 Driver Throughput Testing]] , along with using the logic analyzer.
