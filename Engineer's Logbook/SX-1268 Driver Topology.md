The SX-1268 Driver took a while to build, around 2-weeks of constantly reading datasheets, understanding the different states, and implementing functions. However the driver is now in an operable state, though still untested as of 12/NOV/2026.

Further testing will be done as specified in [[Major Test n1 Driver Throughput Testing]].

The current driver version only operates with LoRa, although the basis is layed to expand it to FSK later, but that is likely not necessary. The driver is not a simple driver, it incorporates an internal state machine, and caches some of the important reused configuration parameters for the chip. Although it is not completely active, as in, it doesn't need it's own "Driver_Update()" function in the main loop. It implements configuration functions that are used to set the parameters of the SX-1268, and operational functions that are used to work the SX-1268, although the driver internals are not simple, the driver interface is. The usage is as follows:

1) Declare the SX-1268 Struct
2) Initialize it with SX68_Init()
3) Set the configuration parameters that you will use, of which there are many but they are well documented in the sx-1268-driver.h function declarations
4) Operate it as necessary, write packet and transmit, or receive and read packet

note: full usage outline for TX and RX are shown in the SX-1268 datasheet in the "application" section.

A full documentation of the driver will be written in [[SX-1268 Handler]] later once the testing is complete.  
