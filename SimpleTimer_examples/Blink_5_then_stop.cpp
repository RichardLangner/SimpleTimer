/*
Blink an LED 5 times then stop.

To stop/start
    Stop    :  timer1.enabled(false);
    Restart :  timer1.enabled(true);

Richard Langner, Sheffield Hackspace member, UK. 13 Jan 2023.
*/
#include "SimpleTimer.h"

SimpleTimer timer1;
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT); 
}

void loop() {
    // Toggle LED every 400ms, repeat 10 times (5 on and 5 off) then stop
	if(timer1.done(400,10) ){
    digitalWrite(ledPin1, !digitalRead(ledPin1));
    }
}
