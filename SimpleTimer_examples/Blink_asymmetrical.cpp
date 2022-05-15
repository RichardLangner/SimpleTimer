/*
Blink asymmetrical - non-blocking.
Switches LED with independent on/off times.
Uses timer1's built-in spare boolean

To stop/start the flashing
    Stop    :  timer1.enabled(false);
    Restart :  timer1.enabled(true);

Richard Langner, Sheffield Hackspace member, UK. 15 May 2022.
*/
#include "SimpleTimer.h"

SimpleTimer timer1;                     // Create a timer
const int ledPin1 = LED_BUILTIN;        // Define where the LED pin

void setup() {
  pinMode(ledPin1, OUTPUT);             // Set LED pin to OUTPUT mode
  digitalWrite(ledPin1, true);          // Turn on the LED
}

void toggleLED(int on, int off){
	if(timer1.done(timer1.boolA ? on:off) ){    // When timer is done
    digitalWrite(ledPin1, timer1.boolA);      // Write to the LED pin
    timer1.boolA=!timer1.boolA;               // Toggle the bool
    }
}

void loop() {
  toggleLED(600,100); // (600ms on, 100ms off) in millis
  // Your other program code here...
}
