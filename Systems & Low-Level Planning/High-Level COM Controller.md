Goal : A system that uses the lower level I2C, UART, and USB controllers to create a very simple interface API, and line management system for sending and receiving data over those lines.

Description : A system built on the low-level communication drivers that is responsible for using RTOS level software to control the drivers and abstract them into simple "Send" and "Receive" functions for each driver, but instead of referencing separate drivers, the COM handler will have a list of available ports (defined at startup using specific functions, before initializing the COM handler, some ports will always be open like USB and EEPROM I2C) with each having a specialized driver. The COM handler's job is to create tasks and use functions for each port to ensure constant data flow.

Note : Each port should have it's own DMA receive task, while send can be a simple function or function pointer that is set when the port opens or at startup.


System Data :
 
