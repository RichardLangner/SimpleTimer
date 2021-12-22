/*
This example schedules functions to run at certain times.
To use the scheduler in your own code, substitute the
    {Serial.println("...");} 
functions with your own functions.

Although the code is in the main program loop() it only runs once 
for each of the print functions.
To repeat the process later in your code, simply reset the timer with
    timer1.enable(true)
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
        if(timer1.eventCount()== 2){Serial.println("Function 1 runs at 2 seconds");}
        if(timer1.eventCount()== 4){Serial.println("Function 2 runs at 4 seconds");}
        if(timer1.eventCount()== 8){Serial.println("Function 3 runs at 8 seconds");}
        if(timer1.eventCount()==12){Serial.println("Function 4 runs at 12 seconds");}
    }
    // Your main program code here
}