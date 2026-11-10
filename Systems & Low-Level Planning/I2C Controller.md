Goal : To create a simplified I2C interface API for communication with peripheral slaves.

Description : Built on top of HAL, it provides a set of functions to be used to on a specific I2C line. One instance of this controller works with exactly one instance of a I2C handler in HAL. It simplifies the logic of communicating with I2C slaves into simple "send and get response" commands, and operates with DMA to not block.


System Data :

-HAL I2C Handler (a pointer to a hi2c# instance)
-Small DMA buffer (non-circular, reset on every call of send-receive)
-Data Arrival Callback (a function pointer to a function that is called when the DMA data read is complete, user could optionally read the "data ready" flag instead)


System Functions :

-I2C_Init (Initializes the Controller data and struct)
-I2C_Send (Puts a message to the chosen address on the line)
-I2C_MemWrite (Writes to a memory address of the chosen device address)
-I2C_SendReceive (Puts a message to the chosen address on the line then opens 
	a DMA buffer of the chosen length to listen for any incoming response)
-I2C_Read (Reads the data sitting in the DMA buffer)
-I2C_MemRead (reads a memory address from the chosen device address)
