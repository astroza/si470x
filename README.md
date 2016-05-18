# Introduction

This project is about interfacing SI470x with A20 SoC (Olinuxino LIME). The unused TWI2 was selected because the tuner chip has a non-standard i2c initialization and needs SDA pin usage exclusivity.

## Pinout

```
 |-----------|                                  |---------------|
 |           |- LOUT ------------------- FMINL -|               |
 | breakout  |- ROUT ------------------- FMINR -|   Olinuxino   |
 |           |- VCC --------------------- 3.3v -|     A20       |
 |           |- GND ---------------------- GND -|               |
 |           |- SDIO -------------------- PB21 -|               |
 |           |- SCLK -------------------- PB22 -|               |
 |           |- SEN xD                          |               |
 |           |- RST --------------------- PC18 -|               |
 |-----------|                                  |---------------|
```
Also, I removed R8 and R3 resistors from Sparkfun breakout because Olinuxino board already has built-in open drain pull up resistors [1].

## Software
The untouched kernel driver does not work because:
* There is no defined IRQ for the device
* The initialization routine leave the chip in a undefined state.

To fix this, what I did was cold start:
* Power down the chip with ENABLE|DISABLE flags (according to page 5 [3])
* Set external crystal
* Wait (500 ms)
* Enable the chip again

And I deleted any interruptions related code 0:) (sadly, RDS support is not working).
## References
- [1] Olinuxino Lime User Manual:
- [2] A20 datasheet
- [3] SI470x Programming Guide: http://cdn.sparkfun.com/datasheets/BreakoutBoards/AN230.pdf
