/*
Blink an LED 5 times, pause, repeat.

To stop/start
    Stop    :  timer2.enabled(false);
    Restart :  timer2.enabled(true);

Richard Langner, Sheffield Hackspace member, UK. 15 May 2022.
*/
#include "SimpleTimer.h"

SimpleTimer timer1, timer2;
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT); 
}

void loop() {
    // Toggle LED after 200ms, repeat 10 times then stop
	if(timer1.done(200,10) ){
    digitalWrite(ledPin1, !digitalRead(ledPin1));
    }

  // Repeat blinking every 5 secs, continuously
  if(timer2.done(5000)){
    timer1.enabled(true);
    } 
}
