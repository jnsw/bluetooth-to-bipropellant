

/*
  Project: ESP32 Bluetooth Mobile Robot
  Board:
  - ESP32 Dev Module (Node32 Lite)
    https://my.cytron.io/p-node32-lite-wifi-and-bluetooth-development-kit
 */

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <HardwareSerial.h>
#include <HoverboardAPI.h>
BluetoothSerial btSerial;

#define BT_NAME "Bierporter One" // Set bluetooth name

#define BUILTIN_LED 2 // LED is active high

#define MAX_SPEED 100

HardwareSerial MotorSerial(1);
boolean btConnected = false;
char key, previousKey;
int motorLeft, motorRight;
long previousMillis = 0;
int timeout = 2000;


// Arduino JoyStick App Variables
int up = 0;
int down = 0;
int right = 0;
int left = 0;
bool button;

long int valX = 0;
long int valY = 0;

bool flag = true;

// BiPropellant API 
int serialWrapper(unsigned char *data, int len) {
 return (int) MotorSerial.write(data,len);
}
HoverboardAPI hoverboard = HoverboardAPI(serialWrapper);

//define Serial Pins GPIO16/17
#define RXD2 16
#define TXD2 17

//Values to send
int sendVal1 = 0;
int sendVal2 = 0;

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);

  Serial.begin(115200);
  delay(20);
  btSerial.begin(BT_NAME);
  delay(20);
  MotorSerial.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(20);
  
  Serial.println("Bierporter startet");
  Serial.println();
  digitalWrite(BUILTIN_LED, LOW);
}

void Joystick() {
  if (btSerial.available())
  {
    int data = btSerial.read();
    if (data <= 100) {
      if (flag) {
        valX = data;
        valX = valX - 50;
        if (valX > 0) {
          right = valX;
          left = 0;
        }
        else if (valX < 0) {
          right = 0;
          left = valX * (-1);
        }
        else {
          right = 0;
          left = 0;
        }
        left = map(left, 0, 50, 0, 255);
        right = map(right, 0, 50, 0, 255);
        flag = false;
      }
      else {
        valY = data;
        valY = (valY - 50) * -1;
        if (valY > 0) {
          up = valY;
          down = 0;
        }
        else if (valY < 0) {
          up = 0;
          down = valY * (-1);
        }
        else {
          up = 0;
          down = 0;
        }
        up = map(up, 0, 50, 0, 255);
        down = map(down, 0, 50, 0, 255);
        flag = true;
      }
    }
    else{
      if(data == 105){
        button = 1;
        digitalWrite(13,HIGH);
      }
      if(data == 106){
        button = 0;
        digitalWrite(13,LOW);
      }
    }
  }
}


void loop(){

  Joystick();

  Serial.print(up);
  Serial.print("   ");
  Serial.print(down);
  Serial.print("   ");
  Serial.print(left);
  Serial.print("   ");
  Serial.print(right);
  Serial.print("   ");
  Serial.println(button);

    
  if(button) {

    if(down == 0) {
      sendVal1 = up;
    } else {
      sendVal1 = -down;
    }

    if(left == 0) {
      sendVal2 = right;
    } else {
      sendVal2 = -left;
    }
    
    sendVal1 = map(sendVal1, 0, 255, 0, MAX_SPEED);
    sendVal2 = map(sendVal2, 0, 255, 0, MAX_SPEED);

    hoverboard.sendPWM(sendVal1, sendVal2, PROTOCOL_SOM_NOACK); 
  } else {
      hoverboard.sendPWM(0, 0, PROTOCOL_SOM_NOACK);
      delay(10);
  }
  // Serial.print(sendVal1);
  // Serial.print("   ");
  // Serial.println(sendVal2);
  delay(10);
}

