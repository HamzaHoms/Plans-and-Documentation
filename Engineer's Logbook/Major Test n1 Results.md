Timing results:

- UART Driver Timing:
  at 500,000bps baud rate, the time per byte is 20us.
  
  at 4-bytes : 
	wUART_WriteTX : 5us
	IDLE ISR : 6us
	HC/FC ISR : 7us
	total bus time : 113us

  at 64-bytes :
  wUART_WriteTX : 9us
  IDLE ISR : 15us
  HC/FC ISR : 15us
  total bus time : 1330us

	What this means:
	
	wUART_WriteTX time per byte = 0.0667 * (n-bytes) + 4.7333
	
	IDLE ISR time per byte = 0.15 * (n-bytes) + 5.4 *provided HC/FC ISR hasn't fired, if it has then the time is a static 3us*
	
	HC/FC ISR time per byte = 0.1333 * (n-bytes) + 6.4667
	
	total bus transaction time per byte = 20.283 * (n-bytes) + 31.8667
	
	all measured in us.
	
	This also means that the total CPU overhead is equal to the wUART_WriteTX time + the IDLE/HC/FC ISR time. and it's percentage of the total transaction time is that divided by total bus transaction time. 
	
	Total CPU Overhead Time = 0.2 * (n-bytes) + 11.2 + 3.0(if HC/FC fire with IDLE Line).



- SX-1268 Driver Timing, TX:
  at 4-bytes :
  avg total timestamp-to-timestamp time : ~16190us
  avg time according to semtech docs : 15488us
  
  at 252-bytes :
  avg total timestamp-to-timestamp time : ~196080us
  avg time according to semtech docs : 194688us
  
  what this means:
  avg time for a single pass (from packet being ready to TX_DONE)=
  725.3 * (n-bytes) + 13290
  ideal time for a single transaction according to semtech docs=
  722.6 * (n-bytes) + 12598
  
  A full pass in my case includes a full IRQ and DIO reset, including an SPI transaction for SX68_ClearIRQStatus, along with a reconfiguration of the payload length using SX68_LoRa_PayloadLength, and re-writing the packets using SX68_WritePacket.
  so by differencing the two time equations we get the following equation for the above mentioned operation's driver overhead=
  2.7 * (n-bytes) + 692, subtracting the SX68_WritePacket's SPI DMA line time at 4MHz, the PA ramp up time (which was 200us for this test), and the official STDBY_RC to TX mode transition time from page 55. since they don't occupy the CPU we get= 
  0.7 * (n-bytes) + 366 ~~ value not 100% accurate, closer to=
  0.7 * (n-bytes) + 350
  
  
- SX-1268 Driver Timing, RX:
  extracting direct equations from the .csv data:
  avg time for a single pass (from RX_DONE to RX_DONE)=
  724.8 * (n-bytes) + 13286
  By comparing the above equation to the ideal semtech time found in the TX section we find that the equation is closer to TX's equation, and that is because the receive cadence is set by the transmitter, so any data here is actually not useful for timing purposes.
  