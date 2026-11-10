Goal : To provide a simple to use interface API for UART, and control the flow of bytes.

Description : Built on top of HAL, it provides a set of functions to be used to on a specific UART line. One instance of this controller works with exactly one instance of a UART line in HAL. It uses a simple FSM to control data-flow and provide flags for busy line, clear line, data arrival, etc. It also incorporates a (should be small) data buffer for DMA data reception.

System Data :

-HAL UART Handler (a pointer to an huart# instance)
-small DMA buffer (a small buffer to accept data from DMA , size set by user in COM handler setup)
-DMA FIFO (another buffer that saves data from the small DMA buffer as soon as it is read so that it does not get over-written by another DMA read, size set by user in COM handler setup)
-Data Arrival Callback function (a function pointer to a function that is called when the "idle_line" interrupt is triggered, user could optionally read the "data ready" flag instead)


System Functions :

-UART_Init (Initializes the UART Controller Instance)
-UART_Send (Sends a provided packet on the UART line and returns an error if something goes wrong)
-UART_Open_DMA (Starts the DMA reception and waits for bytes, can be called once in the beginning as DMA for UART is set to circular by default)
-UART_Close_DMA (Stops the DMA reception)
-UART_Read_FIFO (Reads the first message in the FIFO queue)
-UART_Clear_FIFO (Clears the FIFO to 0s)