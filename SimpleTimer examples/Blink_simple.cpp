/*
Blink simple - Blink an LED continiously without blocking or using interrupts.

To start/stop
    Stop    :  timer1.enable(false);
    Restart :  timer1.enable(true);

Richard Langner, Sheffield Hackspace member, UK. 15 May 2022.
*/
#include "SimpleTimer.h"

SimpleTimer timer1;
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT); 
}

void loop() {
    // Toggle LED every 250ms
	if(timer1.done(250) ){
    digitalWrite(ledPin1, !digitalRead(ledPin1));
    }
}