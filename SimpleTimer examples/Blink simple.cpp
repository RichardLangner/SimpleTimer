/*
Blink simple - Blink an LED without blocking or using interrupts.

Uses timer1 to blink an LED continuously.
    Stop    :  timer1.enabled(false);
    Restart :  timer1.enabled(true);

Richard Langner, Sheffield Hackspace, UK. 17 Dec 2021.
*/
#include "SimpleTimer.h"

SimpleTimer timer1;
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT); 
}

void loop() {
    // Toggle LED every 250ms
	if(timer1.event(250) ){
    digitalWrite(ledPin1, !digitalRead(ledPin1));
    }
}