/*
Blink 5 repeating - without blocking or using interrupts.

Uses a SimpleTimer to blink an LED 5 times, and another to repeat this every 5s.

Use enable to turn on/off
    Stop    :  timer2.enabled(false);
    Restart :  timer2.enabled(true);

Richard Langner, Sheffield Hackspace, UK. 1 Dec 2021.
*/
#include "SimpleTimer.h"

SimpleTimer timer1, timer2;
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT); 
}

void loop() {
    // Toggle LED after 200ms, repeat 10 times then stop
	if(timer1.timedOut(100,10) ){
    digitalWrite(ledPin1, !digitalRead(ledPin1));
    }

  // Repeat blinking every 5 secs, continuously
  if(timer2.timedOut(5000)){
    timer1.enabled(true);
    } 
}
