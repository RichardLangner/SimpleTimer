/*
Example code only, to make it work for you please substitute the
{Serial.println("...");} functions with your own functions.

Although the code is in the main program loop() it only runs once 
for each of the functions.
To repeat the process later in your code, simply reset
the timer with timer1.enable(true)
*/
#include <Arduino.h>
#include "SimpleTimer.h"

SimpleTimer timer1;

void setup()
{
  Serial.begin(74880);
  Serial.println();
}

void loop() {
    // Schedules functions in at preset times
    if(timer1.event(1000,12)){
        if(timer1.eventCount()==2){Serial.println("Function runs at 2 seconds");}
        if(timer1.eventCount()==4){Serial.println("Function runs at 4 seconds");}
        if(timer1.eventCount()==8){Serial.println("Function runs at 8 seconds");}
        if(timer1.eventCount()==12){Serial.println("Function runs at 12 seconds");}
    }
    // Your program here
}