/**
 * HC-SR04 Ultrasonic Sensor with Arduino Leonardo for knitting machine row counter.
 * Date: January 17, 2019
 * 
 * Description:
 *  Connect the ultrasonic sensor to the Arduino as per the
 *  hardware connections below. Run the sketch and open a serial
 *  monitor. The distance read from the sensor will be displayed
 *  in centimeters and inches.
 * 
 * Hardware Connections:
 *  Arduino | HC-SR04 
 *  -------------------
 *    5V    |   VCC     
 *    11    |   Trig     
 *    10    |   Echo     
 *    GND   |   GND
 *  
 * License:
 *  MIT
 *  Author: vadym.vikulin@gmail.com
 */
#include <Keyboard.h>
// Pins
const int TRIG_PIN = 11;
const int ECHO_PIN = 10;
long duration, cm;
int foundHigh=0;
int foundLow=0;
int waitForLow=0;
int rate = 10;

void setup() {

  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
    
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  pinMode(ECHO_PIN, INPUT);
  duration = pulseIn(ECHO_PIN, HIGH);
 
  // Convert the time into a distance (cm)
  cm = (duration/2) / 29.1;
  
  if(cm<=6 && waitForLow==0){
     foundHigh++;
     if(foundHigh>rate){
        waitForLow = 1;
    }
  } else {
    foundHigh=0;
  }
  
  if(cm>8 && waitForLow==1){
      foundLow++;
      if(foundLow>rate){
        waitForLow = 0;
        foundHigh = 0;
        foundLow = 0;
        //press arrow up
        Keyboard.press(0xda);
        delay(100);
        Keyboard.releaseAll();
        delay(200);  
      }
    } else {
         foundLow=0;
    }
}
