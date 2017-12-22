#include "Arduino.h"
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

int led = 13;
int arrLen = 3;
int HOUR_ON[] =    {12, 12, 12};
int MINUTE_ON[] =  {33, 36, 38};
int HOUR_OFF[] =   {12, 12, 13};
int MINUTE_OFF[] = {35, 37,  1};
// state = -1 means OFF, otherwise while ON
// it takes the value of the array element: 0, 1 ,2
short int state = -1;
int i;


void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");
  pinMode(led, OUTPUT);
}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    
    for (i=0; i < arrLen; i++){
      if (tm.Hour == HOUR_ON[i] && tm.Minute == MINUTE_ON[i] && state == -1){
        state = i;
        digitalWrite(led, HIGH);
      }
    }
    if (state > -1){
      if (tm.Hour == HOUR_OFF[state] && tm.Minute == MINUTE_OFF[state]){
        state = -1;
        digitalWrite(led, LOW);
      }
    }      
  
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(10);
}
