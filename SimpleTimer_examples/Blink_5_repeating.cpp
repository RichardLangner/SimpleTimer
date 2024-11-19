/*
Use SimpleTimer to blink an LED 3 times (takes 600ms), then repeat every 5 secs.

To stop/start
    Stop    :  timer2.enabled(false);
    Restart :  timer2.enabled(true);

Richard Langner, Sheffield Hackspace member, UK. 13 Jan 2023.
*/

#include <Arduino.h>
#include "SimpleTimer.h"

SimpleTimer timer1, timer2;
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT); 
}

void loop() {
  // Toggle LED every 200ms, 6 times (3 on and 3 off), then disable
	if(timer1.done(200,6) ){
    digitalWrite(ledPin1, !digitalRead(ledPin1));
    }

  // Restart the 3 blinks every 5 secs
  if(timer2.done(5000)){
    timer1.enabled(true);
    } 
}
