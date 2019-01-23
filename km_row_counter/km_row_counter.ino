/*##############################################################################
 Author:
 * Vadym Vikulin (23-01-2019)
 * email: vadym.vikulin@gmail.com
 
 Description:
 * Knitting machine row counter with GP2Y0D805Z0F sensor and Arduino Leonardo.
 * Check periodically the OUT pin of the sensor GP2Y0D805Z0F, if it is encountered
 * an obstacle (OUT = 0), the LED connected to pin 13 of Arduino is turned on and arrow up is pressed.
 * The SLP pin that puts the sensor in standby mode should be connected to 5V or to a high logic level
 
 Connections:
 * BOARD -> ARDUINO
 * Vcc   -> 5V
 * GND   -> GND
 * OUT   -> PIN 2
##############################################################################*/

#include <Keyboard.h>
// Define constants and variables
const int  STATE = 2;                 // sets pin 2 for sensor reading
int r_state = 0;                      // reset to zero the variable used to read the state of the OUT pin of the sensor
int foundHigh=0;
int foundLow=0;
int waitForLow=0;
int rate = 10;
 
// Initialization
void setup(){                        
  pinMode (STATE, INPUT);              // sets pin 2 as digital input 
}

// main loop
void loop(){
  r_state = digitalRead(STATE); // reads the status of the sensor

  if(r_state == 0 && waitForLow==0){
     foundHigh++;
     if(foundHigh>rate){
        waitForLow = 1;
    }
  } else {
    foundHigh=0;
  }
  
  if(r_state != 0 && waitForLow==1){
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

