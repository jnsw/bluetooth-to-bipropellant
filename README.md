
# bluetooth-to-bipropellant (currently not maintained)
### How to connect a Smartphone to a Hoverboard with the help of an ESP32 via bluetooth or in short *just a quickstart for having fun*
![](.github/example1.gif)
### Happy hacking!


## Prerequisites

 - a hoverboard flashed with the firmware [bipropellant](https://github.com/bipropellant)/**[bipropellant-hoverboard-firmware](https://github.com/bipropellant/bipropellant-hoverboard-firmware)** 
 <br>(configured with **#define CONTROL_TYPE USART2_CONTROLLED**)
 <br>(you can use parts out of [this tutorial](https://github.com/NiklasFauth/hoverboard-firmware-hack/wiki/Build-Instruction:-TranspOtter) to get to know, how to flash the board - also you need an 
 - ST-Link V2 USB for flashing the firmware onto your board - **don't forget not to power the hoverboard mainboard with the usb stick - it will fry it** 
 - the app *Arduino Bluetooth Joystick* ~~([from Play Store](https://play.google.com/store/apps/details?id=com.juan.arducontrol))~~ (removed from PlayStore - search for "com.juan.arducontrol" at your own risk)
 - an ESP32 (I used an Wemos styled one, but it should work with every version) 

## Wiring
|ESP32|hoverboard mainboard|
|--|--|
| GND | GND |
| GPIO16 | PA2/TX/ADC1 |
| GPIO17 | PA3/RX/ADC2/PPM |

(connect ESP32 to an 5V source, like a powerbank or use a voltage converter on the left sensor cable/output)

(if you want to use different GPIOs on the ESP32, change it in the code accordingly)

**IMPORTANT: DO NOT POWER THE ESP32 with that 15V line, it will burn that board!**

## Flashing

For flashing the ESP32, I used Visual Studio Code with PlatformIO, maybe you need to change the board type, if its not a wemos-like ESP32, but try it for yourself! Write me, if you worked it out the other way.

## Using
 - Turning on the hoverboard as usual by pressing the on button once
 - Connect to *Bierporter One* (bluetooth name of the ESP32 you can also change in the code) via Bluetooth
 - Open the controller app and choose your device
 - Use the D-pad to drive around and by holding the A button it will let you drive faster (you can change the both speeds in the config part of the code)
 - Have fun!
 
## Hardware
![Hoverboard Mainboard Pinout](https://raw.githubusercontent.com/NiklasFauth/hoverboard-firmware-hack/master/pinout.png)
picture from 
[NiklasFauth](https://github.com/NiklasFauth)/**[hoverboard-firmware-hack](https://github.com/NiklasFauth/hoverboard-firmware-hack)**

## Libraries used
 - [jpmonrest](https://github.com/jpmonrest)/**[ArduControl](https://github.com/jpmonrest/ArduControl)** - for the steering wheel interface to the corresponding [app](https://play.google.com/store/apps/details?id=com.juan.arducontrol)
 - [bipropellant](https://github.com/bipropellant)/**[bipropellant-hoverboard-api](https://github.com/bipropellant/bipropellant-hoverboard-api)** - to communicate to the freshly flashed hoverboard
