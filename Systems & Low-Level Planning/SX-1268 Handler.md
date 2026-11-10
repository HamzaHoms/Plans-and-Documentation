Goal : Provide a simpler interface that abstracts away the Op-Codes of the SX-1268 into simple dostuff() functions.


Description : This system will abstract away the direct op-codes and replace them with interfacing functions, register read-writes will become setting functions, multi-step mode changes will become single function calls, and EXTI implementation functions will be provided to handle the system's state-machine. The system is a little more complex than a stateless driver as the SX-1268 has a lot of features that are very useful, and thus it will have a state-machine that tracks stuff like current mode of the chip, TX success and failure, RX packet in reception, Pre-amble detect, time-stamps, etc.. 


System Data : 
-struct GPIOx :
	-hspi* : pointer to the HAL SPI handler.
	-cs_gpio : pin and port of the CS line.
	-rs_gpio : pin and port of the NRST line of the SX-1268.
	-bind_gpio : pin and port of the busy indicator line of the SX-1268

-struct DIOx :
	-dio1_gpio : pin and port of the DIO1 line.
	-dio2_gpio : pin and port of the DIO2 line.
	-dio3_gpio : pin and port of the DIO3 line.
	note : if dio2 is being used for the RF switch, or dio3 is being used for the TCXO then those gpios can be left NULL.

-struct IRQx :
	-uint16 IRQ_flags : map of the 10 irqs that could come from the SX-1268.
	-irq_flag1 : is set to true when an IRQ is detected on DIO1 pin.
	-irq_flag2 : is set to true when an IRQ is detected on DIO2 pin.
	-irq_flag3 : is set to true when an IRQ is detected on DIO3 pin.

-struct DATAx :
	-uint8 tx_buffer {256} : the buffer that the "Write_TX_Packet" function will send as a tx packet, it can be partially filled and sent for variable length packets.
	-uint8 tx_size : size of the next tx_packet to be sent.
	-tx_sts : status of the tx buffer, busy if it is writing, clear otherwise.
	-uint8 rx_buffer {256} : the buffer that the "Read_RX_Packet" function will read the last rx packet into.
	-uint8 rx_size : size of the last received rx packet.
	-rx_sts : status of the rx buffer, busy if it is being written to, clear otherwise.

-mode : the mode of operation that the SX-1268 should be in to the knowledge of the stm32.


System Functions : 

Lower Level Functions :
	-Set_CS (SX1268* dev, uint8 cs_state)
	-Read_BIND (SX1268* dev)
	-Cmd_TXRX (SX1268* dev, uint8 opcode, uint8* args, uint16 arg_len, uint8* rec_val, uint16 expected_rec_len)
	-Buffer_TX (SX1268* dev, uint8* write_buf, uint16 write_len)
	-Buffer_RX (SX1268* dev, uint8* read_buf, uint16 read_len)
	note : since all command transactions receive the device status directly, the "mode" value can be updated directly.

Higher Level Functions :
	-SX68_Init(SX1268* dev, SPI_HandleTypeDef* hspi, GPIO* cs_gpio, GPIO* nrst_gpio, GPIO* bind_gpio)
	-SX68_SetStdby(SX1268* dev, CONF stdby_conf)
	-SX68_SetSleep(SX1268* dev, CONF sleep_conf)
	-SX68_SetFrequency(SX1268* dev, CONF freq)
	-SX68_ConfLoRa(SX1268* dev, CONF sf, CONF bw, CONF cr, CONF ldopt)



