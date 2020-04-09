
# Bluetooth-to-Bipropellant 
## Connecting Smartphone to Hoverboard with ESP32 for RC purposes


Prerequisites:

 - a hoverboard flashed with the firmware [bipropellant](https://github.com/bipropellant/bipropellant-hoverboard-firmware) (configured with *#define CONTROL_TYPE USART2_CONTROLLED*)
 - the app *Arduino Bluetooth Joystick* ([from Play Store](https://play.google.com/store/apps/details?id=com.juan.arducontrol))
 - an ESP32 (I used an Wemos styled one, but it should work with every version)

### Wiring
|ESP32|hoverboard mainboard|
|--|--|
| GND | GND |
| GPIO16 | PA2/TX/ADC1 |
| GPIO17 | PA3/RX/ADC2/PPM |

(connect ESP32 to an 5V source, like a powerbank or use a voltage converter on the left sensor cable/output)

**IMPORTANT: DO NOT POWER THE ESP32 with that 15V line, it will burn that board!**

## Hardware
![Hoverboard Mainboard Pinout](https://raw.githubusercontent.com/NiklasFauth/hoverboard-firmware-hack/master/pinout.png)

![Wemos ESP32 pinout](.github/esp32-pinout.jpg)
