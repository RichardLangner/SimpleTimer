/* 
Blink (up to) a 5 digit number on a single LED, with 500ms gap between each digit.
Returns 'true' when it completes a group of digits, then repeats after several seconds. 
The flash 'on' and 'off' period is 200ms each. A zero is represented by 1000ms 'on'.

FlashDigits is a class, so you can have several independent flashers at once.
To create a Flashdigits object called 'flasher1':
   FlashDigits flasher1;  

Written by Richard Langner, Sheffield Hackspace, UK 21 May 2023.
Latest code and examples on github.com/RichardLangner/SimpleTimer
*/

#include "SimpleTimer.h"			// github.com/RichardLangner/SimpleTimer
#include "flashNumber.h"            // github.com/RichardLangner/SimpleTimer/tree/main/SimpleTimer_examples/
FlashDigits flasher1;                // Create an instance of a flasher object

int ledPin = D4;                    // Wemos D1 mini LED pin, active LOW
int counter=0;                      // How many time the complete number flashes

void setup() {
	Serial.begin(74880);            // Wemos D1 mini default baud rate
	pinMode(ledPin, OUTPUT);        // Set LED pin to be an output
    digitalWrite(ledPin, HIGH);     // LED is active LOW
    delay(3000);                    // Not required
    flasher1.setup(ledPin, LOW);    // Define the LED pin and its active level
    Serial.printf( "Flasher enabled = %s\n", (flasher1.enabled() ? "Yeh": "Nope"));
}

void loop() {
    if(flasher1.flash(counter, ledPin, LOW, 0)){
        Serial.printf("Counter has just flashed %d\n", counter++ );
        if(counter >11){
            flasher1.enabled(false);
            Serial.printf( "Flasher enabled = %s\n", (flasher1.enabled() ? "Yeh": "Nope"));
            }
    };
}