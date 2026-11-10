this function is implemented as part of the [[SX-1268 Handler]] low level functions, the command transaction is split into two chunks, the first chunk sends the op-code and arguments, and reads the status return values. The second chunk sends NOPs and reads the expected return values if any are present. it works as follows :

1) read the busy pin of the sx1268, if busy, wait until it clears or a timeout is reached.
2) initialize the memory tx and rx buffers that will be used for the first chunk transaction of the command using the number of arguments for the size while adding one byte for the opcode and one byte for the NOP-Status space in the case of an expected return.
3) Pull CS low and execute the first chunk transaction.
4) read the return value of the HAL_SPI function and return early if it failed.
5) read the return rx buffer for this transaction and use the last STATUS byte to update the status of the internal state machine on the stm32, and make sure the transaction command completed correctly.
6) if the transaction completed incorrectly return an error.
7) execute the read into the ret_val buffer.
8) if the HAL_SPI function errored out return an error.
9) Pull CS high and return a success.

note 1: Expected return length and argument length must match the lengths listed on the datasheet for that command. 