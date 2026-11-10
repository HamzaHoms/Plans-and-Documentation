The project stack-up explanation and plan will be split up into 3 layers : 
1. [[Hardware Layer]] : What's physically going to be on the board.
2. [[Firmware Layer]] : The base firmware that cannot be altered, like communication protocols, comm handlers, RTOS, etc..
3. [[Software Layer]] : Anything concerning the scripts and interpreter. 

Goal of the Project :
The final goal of this project is to create a reliable and easy-to-use technology which allows the connection and control of multiple different families of devices/vehicles/platforms onto a single dynamically routed mesh network. The technology is hot-swappable with minimal down-time, simple to understand and write scripts for, and supports as many platforms as possible, all done through a simple API. Simply put, the project combines a mesh network with a companion computer in one package. The network simply acts as a link between nodes, while each individual node's companion computer can be configured using a few user-made scripts to act differently and be compatible with whatever target platform is needed.

Structure :
The device itself is minimalistic. It will have two microcontrollers, one acting as a script controller and the other as a network router. A LoRa Radio module, specifically LoRa because it provides suitable ranges at low Spread-Factors, while still having a good data-rate. and a group of ports from different protocols broken out, a port from each of the common protocols will do, so 1 port from each : UART, SPI, I2C, USB. And lastly a good antenna suitable for the low power communication of the LoRa device. The actual setup of the device will be very simple provided you know the expected communication protocol of the target device, it will be as simple as writing a "setup" script which initializes the target port on the device and defines different used packets and wraps the provided firmware functions into clean functions, basically running once at startup to initialize the LUA interpreter and packet LUT, and create the function instances. And writing a "node-behavior" script which is the script that constantly runs on the script controller MCU, parsing messages from both the network side and the target side, while executing some simple or complex algorithm.

Structure Example :
a good example would be pairing the device with an ardupilot flighcontroller. The device would connect to the FC over UART, the setup script would initialize the UART port with a certain baud rate and define certain expected packets and functions that operate with the MAVlink protocol, and the node-behavior script could have a custom made "GO-TO" algorithm where if the node receives a special packet from a ground station node carrying a specific GPS coordinate, it would send a GO-TO MAVlink command to the FC with the specified GPS waypoint.


