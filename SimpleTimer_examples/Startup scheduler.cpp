/*
Example code only, to make it work for you please substitute the
{Serial.println("...");} functions with your own functions.

Although the code is in the main program loop() it only runs once 
for each of the functions.
To repeat the process later in your code, simply reset
the timer with timer1.enabled(true)

Richard Langner, Sheffield Hackspace member, UK. 15 May 2022.
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
    // Schedules functions at preset times
    if(timer1.done(1000,12)){
      timer1.intA++;
      if(timer1.intA== 2){Serial.println("Function runs once at  2 seconds");}
      if(timer1.intA== 4){Serial.println("Function runs once at  4 seconds");}
      if(timer1.intA== 8){Serial.println("Function runs once at  8 seconds");}
      if(timer1.intA==12){Serial.println("Function runs once at 12 seconds");}
    }
    // Your program here
}