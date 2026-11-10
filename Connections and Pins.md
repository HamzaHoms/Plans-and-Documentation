Currently the Inter-chip connections are as follows :
USB 1x from SC to target 
UART 3x from SC to target
I2C 1x from SC to target
UART 1x from SC to RC
SPI 1x from RC to LoRa
I2C 1x from RC and 1x from SC to EEPROM

These lines require some arbitration to manage data-flow. Most importantly the UART from SC to RC and vice-versa, there are multiple ways to arbitrate messages over this line :
-The simplest is to just open a circular UART buffer and use the "ReceiveToIdle" setting to set a "packet has arrived" flag and read the incoming data, this is the simplest as it is just a normal UART with all of the arbitration done in software, however it requires careful management of the ring-buffer and message size to ensure no over-run happens.
-A more complex way would be polling an interrupt pin from the RC to the SC that indicates a sort of "message ready to send" flag. This could be used to avoid over-runs and simplify the software arbitration, however it is more electrically complex.
-Using a more complex protocol like RS232 though this might be overkill. 

Most likely I will choose the first option with a larger ring-buffer (possible 1kb) then use COBS for the actual data. See https://github.com/MaJerle/stm32-usart-uart-dma-rx-tx for a good strategy and especially the "UART IDLE line detection + DMA HT & TC interrupts with RTOS" section.

This UART communication scheme will most likely be used across all 4 UART peripherals, with COBS being an optional setting.
