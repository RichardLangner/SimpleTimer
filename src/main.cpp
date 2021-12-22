/*
Schedules functions- although it is in loop(), it only runs once.
To run it again from another part of your program use -
        schedule.enable(true);

Richard Langner, Sheffield Hackspace, UK. 17 Dec 2021.
*/
#include <Arduino.h>
#include "SimpleTimer.h"

SimpleTimer mySchedule;     // Create a timer
unsigned long offset;

void setup(){
  Serial.begin(74880);  // Select your own speed
  offset=millis();
}


void loop() {

    if(mySchedule.event(10,8)){ // One event per second, so no need to go more than 8 events
        Serial.printf("%4lums event %d\n",(millis()-offset),mySchedule.eventCount());
        if(mySchedule.eventCount()==6){Serial.printf("%4lums event %s \n",(millis()-offset), "event counter=6");}
    }
    // Your program here
}