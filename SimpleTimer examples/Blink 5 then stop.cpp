/*
Blink 5 repeating -without blocking or using interrupts.

Uses a SimpleTimer to blink an LED 5 times then stop.

Use enable to turn on/off
    Stop    :  timer1.enable(false);
    Restart :  timer1.enable(true);

Richard Langner, Sheffield Hackspace, UK. 22 Dec 2021.
*/
#include "SimpleTimer.h"

SimpleTimer timer1;
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT); 
}

void loop() {
    // Toggle LED after 200ms, repeat 10 times then stop
	if(timer1.event(200,10) ){
    digitalWrite(ledPin1, !digitalRead(ledPin1));
    }
}
