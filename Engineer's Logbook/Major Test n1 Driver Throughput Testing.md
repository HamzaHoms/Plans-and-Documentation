Aim:
To verify the ruggedness of my drivers and try to measure a rough value of their throughput as is.

Test Parameters:
1) Failures - Speed measurement: seeing how many transactions result in dropped, missing, or corrupted data per transfer speed and density settings.
2) Switching measurement: seeing how the driver reacts when it constantly has to switch between TX and RX, measures stuff like speed of switch, and blind spot length.
3) Overload Capacity: seeing how the driver reacts when bombarded with high density data transfers.
4) Latency measurement: seeing how long it takes for a data packet to get from one end-point to another.
Parameter Specific to SX-1268:
- Range test: seeing how far the chip can communicate at specific SF and Power settings. The max I can probably get is roof of E1 to Mimarlik Platform which is about 290m with trees and buildings around, so maybe equivalent to 1km in ideal conditions. 

Plan for the Tests:
The 4 main measurement parameters will be integrated into the code of the MCUs where tests will be ran with a computer running a C++ program in the loop, the two nodes I have currently as of 12/NOV/2026 will form a half-duplex pipeline from the C++ program running back into itself, so the C++ program can measure the full latency and see the values it is getting. Some tests will be ran with the C++ program as part of the test, some will be ran purely on the MCUs with the C++ program just recording data.

(1) : Can be measured by setting a baud rate for each driver, recording it, then sending increasingly longer transactions with an expected value, if the expected value is not seen at the receiver end, it is considered a failed transaction, one failure is added to the (1) measurement per dropped or corrupted transaction. The expected values will be a 32-bit number appended to the end of each dummy buffer, the 32-bit number get's incremented after each transaction. The test starts at the C++ program, it sends a uint32 number we will call num, num is then sent to the SC1 through USB1, SC1 gets it, records that it got it, and records what num+1 will be. SC1 then transfers it to RC1 through UART1, where RC1 does the same. RC1 transfers it to RC2 through LoRa, RC2 records again. RC2 transfers to SC2 through UART2, where SC2 records num and sends it back to the computer through USB2. Once the computer sees that the number it sent out has arrived it records a success, if the transaction dropped any part of the way through, a failure will be recorded on both the C++ program and the relevant MCU step that never saw num. The failure positions can then be extracted at the end of the test.

(2) : Will done the same as (1) but the SC2 echoes the data back to where it came from instead of completing the loop, each MCU will have measurements for the turn-around time of the drivers, failures will also be recorded here. Good to note that since UART is completely full-duplex, it will most likely not be an issue unless the speed is so fast that it over-writes itself.

(3) Same as (1) but instead of an ever-increasing packet size, we have a max-size data packet get sent out at a constant time interval, this test mainly exists to see if the drivers lock up or cause crashes, will not really be a numerical measurement for this test.

(4) Similar to (2) but keeping the packet size at constant steps (eg. 4 bytes, then 8 bytes, then 32 bytes, etc..) and starting a microsecond  timer on the SC1 once the packet Gets to it and stopping the timer once the echo is seen, then taking the time/2 to find how long it took, average it over a couple hundred packets and you can find the average latency. 

(SX-1268 test) This one is the simplest, simply have a program that sends out a value on one node, and have the other node do something based on the value, like beep a buzzer. Then put one node at Mimarlik platform, and the other at E1 roof and see if they connect at the lowest useable SF and highest BW. If they do then that's good enough for any further testing.