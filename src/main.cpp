/*
  Project: bt2bp
  Board: ESP32 Wemos
  https://github.com/jnsw/bt2bp
 */

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <HardwareSerial.h>
#include <HoverboardAPI.h>
BluetoothSerial btSerial;

#define BT_NAME "Bierporter One" // Set bluetooth name

#define BUILTIN_LED 2 // LED is active high


//set two speeds
#define MAX_SPEED_SLOW_PRE 15
#define MAX_SPEED_FAST_PRE 40
int maxSpeed = 100;

#define MAX_SPEED_SLOW MAX_SPEED_SLOW_PRE * 10
#define MAX_SPEED_FAST MAX_SPEED_FAST_PRE * 10

// boolean btConnected = false;
// char key, previousKey;
// int motorLeft, motorRight;
// long previousMillis = 0;
// int timeout = 2000;
// 


// for "jpmonrest/ArduControl"
int up = 0;
int down = 0;
int right = 0;
int left = 0;
int updown = 0;
int leftright = 0;
bool button;

long int valX = 0;
long int valY = 0;
bool flag = true;
bool reverseUpDown = true;
bool reverseLeftRight = false;
//

// BiPropellant API 
#define RXD2 16
#define TXD2 17
HardwareSerial MotorSerial(1);

int serialWrapper(unsigned char *data, int len) {
 return (int) MotorSerial.write(data,len);
}
HoverboardAPI hoverboard = HoverboardAPI(serialWrapper);


//Values DO NOT CHANGE
int sendVal1 = 0;
int sendVal2 = 0;
int reverseUpDownVal = reverseUpDown ? -1 : 1;
int reverseLeftRightVal = reverseLeftRight ? -1 : 1;


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

// "jpmonrest/ArduControl" joystick mini library 
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
        leftright = map(valX, -50, 50, -255, 255);
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
        updown = map(valY, -50, 50, -255, 255);
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


void loop() {
  Joystick();
  //JoyStick Values for debug
  Serial.print(up);
  Serial.print("   ");
  Serial.print(down);
  Serial.print("   ");
  Serial.print(left);
  Serial.print("   ");
  Serial.print(right);
  Serial.print("   ");
  Serial.print(updown);
  Serial.print("   ");
  Serial.print(leftright);
  Serial.print("   ");
  Serial.println(button);
  
  // Press A to set more speed 
  if(button) {
    maxSpeed = MAX_SPEED_FAST;
  } else {
    maxSpeed = MAX_SPEED_SLOW;
  }
  
  //Map values of controller to speed config
  sendVal1 = map(updown, 0, 255, 0, maxSpeed);
  sendVal2 = map(leftright, 0, 255, 0, maxSpeed);

  //Send Values to Hoverboard
  hoverboard.sendPWM(sendVal1 * reverseUpDownVal, sendVal2 * reverseLeftRightVal, PROTOCOL_SOM_NOACK); 
  // Debug PWM Values
  // Serial.print(sendVal1); Serial.print("   "); Serial.println(sendVal2); 
  delay(10);
}

