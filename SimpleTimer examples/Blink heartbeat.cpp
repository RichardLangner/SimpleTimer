/*
Heartbeat : a pulsing glow from an LED without blocking or using interrupts.

Use enable to turn on/off e.g.
    Stop    :  timer1.enabled(false);
    Restart :  timer1.enabled(true);
    
Richard Langner et Al, Sheffield Hackspace, UK. 1 Dec 2021.
*/
#include "SimpleTimer.h"

SimpleTimer timer1;
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT);
}

void heartbeat(){
  static bool b=true, direction;;
  static int on=18, off=2, toggles, stepCounter;

	if(timer1.event(b ? off:on) ){
    digitalWrite(ledPin1, b);
    b=!b; toggles += 1;
    if(toggles == 4){
      toggles=0; stepCounter++;
      if(stepCounter >= (17)){stepCounter =0;  direction=!direction;}
      if(direction){on++; off--;} else {on--; off++;}
    }
  }
}

void loop() {
    heartbeat();
  }
