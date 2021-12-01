/*
Blink asymmetrical -  without blocking or using interrupts.

Switch anything with independent on/off times.

Use enable to turn on/off
    Stop    :  timer1.enabled(false);
    Restart :  timer1.enabled(true);

Richard Langner, Sheffield Hackspace, UK. 1 Dec 2021.
*/
#include "SimpleTimer.h"

SimpleTimer timer1, timer2;
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT);
  timer2.enabled(false);
}

void switchOnOff(int on, int off){
  static bool b=true;
  
	if(timer1.timedOut(b ? off:on) ){
    digitalWrite(ledPin1, b);
    b=!b;
    }
}

void loop() {
  
  switchOnOff(600,100); // (600ms on, 100ms off) in millis
 
}
