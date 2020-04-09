
# Bluetooth-to-Bipropellant 
### Connecting Smartphone to Hoverboard with ESP32 for RC purposes


## Prerequisites

 - a hoverboard flashed with the firmware [bipropellant](https://github.com/bipropellant/bipropellant-hoverboard-firmware) (configured with *#define CONTROL_TYPE USART2_CONTROLLED*)
 - the app *Arduino Bluetooth Joystick* ([from Play Store](https://play.google.com/store/apps/details?id=com.juan.arducontrol))
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

For flashing the ESP32, I used Visual Studio Code with PlatformIO, maybe you need to change the board type, if its not Wemos-like ESP32, but try for yourself!

## Using
 - Turning on the hoverboard as usual
 - Connect to *Bierporter One* via Bluetooth
 - Open Controller App and connect to the device again
 - Drive around with slow speed and by holding A it will drive with faster speeds (you can change the speed in the config part of the code)
 - Have fun!
 
## Hardware
![Hoverboard Mainboard Pinout](https://raw.githubusercontent.com/NiklasFauth/hoverboard-firmware-hack/master/pinout.png)
picture from 
[NiklasFauth](https://github.com/NiklasFauth)/**[hoverboard-firmware-hack](https://github.com/NiklasFauth/hoverboard-firmware-hack)**


