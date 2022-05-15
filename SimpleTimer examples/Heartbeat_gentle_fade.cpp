/*
Heartbeat : LED fading up and down slowly.

To stop/start the heartbeat
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

void heartbeat(){
    if(timer1.done(50)){
        analogWrite(ledPin1, timer1.intA);    // active LOW LED
        if(timer1.intA >245){timer1.boolA=true;}        // Don't go off completely
        if(timer1.intA <10){timer1.boolA=false;}         // Full brightness
        timer1.intA =(timer1.boolA ? timer1.intA-=10 : timer1.intA+=10);
    }
}

void loop() {
    heartbeat();
    // Your code here
}
