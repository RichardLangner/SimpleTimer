/*
Heartbeat : LED pulsing on fast, then fading.
Works with active HIGH or LOW LED - comment out as appropriate in the heartbeat() function.

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

void heartbeatpulse(){
    if(timer1.done(50)){analogWrite(ledPin1, (timer1.intA +=10) % 255);}    // active LOW LED
    //if(timer1.done(50)){analogWrite(ledPin1, 255- (timer1.intA +=10) % 255);} // active HIGH LED
}

void loop() {
    heartbeatpulse();
    // Your code here
}
