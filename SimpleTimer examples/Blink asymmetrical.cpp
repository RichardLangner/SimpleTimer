/*
Blink asymmetrical -  without blocking or using interrupts.

Switch LED with independent on/off times.

Use enable() to turn on/off the flashing
    Stop    :  timer1.enable(false);
    Restart :  timer1.enable(true);

Richard Langner, Sheffield Hackspace, UK. 22 Dec 2021.
*/
#include "SimpleTimer.h"

SimpleTimer timer1, timer2;
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT);
  timer2.enable(false);
}

void switchOnOff(int on, int off){
  static bool b=true; // Remember the state through calls
	if(timer1.event(b ? off:on) ){
    digitalWrite(ledPin1, b);
    b=!b;
    }
}

void loop() {
  switchOnOff(600,100); // (600ms on, 100ms off) in millis
  // Your other program code here...
}
