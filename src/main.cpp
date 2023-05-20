/* 
Blink (up to) a 5 digit number on a single LED, with 500ms gap between each digit.
Returns 'true' when it completes a group of digits, then repeats after several seconds. 
The flash 'on' and 'off' period is 200ms each. A zero is represented by 1000ms 'on'.

Written by Richard Langner, Sheffield Hackspace, UK 20 May 2023.
Latest code and examples on github.com/RichardLangner/SimpleTimer
*/

#include "SimpleTimer.h"			// github.com/RichardLangner/SimpleTimer
#include "flashNumber.h"            // github.com/RichardLangner/SimpleTimer/tree/main/SimpleTimer_examples/

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int counter=98;                      // How many time the complete number flashes

void setup() {
	Serial.begin(74880);            // Wemos D1 mini default baud rate
	pinMode(ledPin, OUTPUT);        // Set LED pin to be an output
    digitalWrite(ledPin, HIGH);     // LED is active LOW
    delay(3000);                    // Not required
}

void loop() {
    if(flashNumber(counter, 0, ledPin, LOW)){
        Serial.printf("Counter has just done ------------------------------------- %d\n", counter++ );
    };
}