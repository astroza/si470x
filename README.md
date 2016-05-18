# Introduction

This project is about interfacing SI470x with A20 SoC (Olinuxino LIME). The unused TWI2 was selected because the tuner chip has a non-standard i2c initialization and needs SDA pin usage exclusivity.

## Pinout

```
 |-----------|                                  |---------|
 |           |- LOUT ------------------- FMINL -|         |
 | breakout  |- ROUT ------------------- FMINR -|   A20   |
 |           |- VCC --------------------- 3.3v -|         |
 |           |- GND ---------------------- GND -|         |
 |           |- SDIO -------------------- PB21 -|         |
 |           |- SCLK -------------------- PB22 -|         |
 |           |- SEN xD                          |         |
 |           |- RST --------------------- PC18 -|         |
 |-----------|                                  |---------|
```
