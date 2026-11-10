1. Add TX FIFO to the USB wrapper and add a timeout for the TX Busy block so the bus doesn't lock up.
2. Using the experience and similar algorithms as the initial uart controller, re-write it to be cleaner, and easier to setup, aka no need to go through 3 different files defining and declaring functions for the interrupts to work. Also add a TX FIFO.
