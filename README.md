# SI470X V4L2 driver
![Project](https://github.com/astroza/si470x/blob/master/doc/project.png)

This project is about interfacing SI470X with A20 SoC (Olinuxino LIME). The unused TWI2 was selected because the tuner chip has a non-standard i2c initialization and needs SDA pin usage exclusivity.

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
Also, **I removed R8 and R3 resistors** from Sparkfun breakout because Olinuxino board already has built-in open drain pull up resistors [1].

## Software
The untouched kernel driver does not work because:
* There is no defined IRQ for the device
* The initialization routine leave the chip in an undefined state.

To fix this, what I did was cold start:
* Power down the chip with ENABLE|DISABLE flags (according to page 5 [3])
* Set external crystal
* Wait 500 ms for calibration
* Enable the chip again

And also, I deleted any interruptions related code 0:) (sadly RDS support is not working).

Once you install the modified driver, you can load it as follows:
```bash
	reset_tuner_si470x
	modprobe radio_i2c_si470x
	echo "si470x 0x10" > /sys/bus/i2c/devices/i2c-2/new_device
```
> **reset_tuner_si470x** is a program included in this repository. If you want to know how the **last line** works, please check https://www.kernel.org/doc/Documentation/i2c/instantiating-devices.

Later, you can tune any FM radio frequency via /dev/radio0 V4L2 interface. The project http://benpfaff.org/fmtools/ is useful for you here.

### Audio capturing
![sunxi codec](https://github.com/astroza/si470x/blob/master/doc/codec.png)

Diagram above [2] says first value ADCIS=1 corresponds to FMin. ALSA sunxi codec driver has a control "ADC Input Mux" to select the audio source for capturing, configured as a 7 state percentage bar. If 100/7=˜14, the first value in the bar (14) is for FMin.
![sunxi codec](https://github.com/astroza/si470x/blob/master/doc/alsa.png)

Finally!, you can test the radio output:

**Terminal 1**
```bash
arecord -D hw:0,0 -c 2 -V stereo /dev/null
```
**Terminal 2**
```bash
fm -d /dev/radio0 -t 0 -T forever 89.70 100%
```
## References
- [1] Olinuxino Lime User Manual: https://www.olimex.com/Products/OLinuXino/A20/A20-OLinuXino-LIME/resources/a20-olinuxino-lime-um.pdf
- [2] A20 datasheet: http://dl.linux-sunxi.org/A20/A20%20Brief%202013-02-27.pdf
- [3] SI470x Programming Guide:http://cdn.sparkfun.com/datasheets/BreakoutBoards/AN230.pdf
