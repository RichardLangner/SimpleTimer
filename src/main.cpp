/* 
Blink number, up to 5 digits, with 1 1000ms gap between each digit. Then repeats afet 2000ms.
Each flash 'on' is 200ms. A zero is 1000ms on. The flash 'off' time is 200ms.
Written by Richard Langner, Sheffield Hackspace, UK 23 April 2023.
*/

#include "SimpleTimer.h"					// Include the Timer class definition.
void flashDigit(int num);
int ledPin = D4;                            // Wemos D1 mini
#define DEBUG Serial.printf("%3d P = %2d, digit = %d, F = %d, LED will be %s for ms = %4d ms\n", __LINE__, arrayPointer, array[arrayPointer], flashCounter, digitalRead(ledPin) ? "Off":"On ", ms);


void setup() {
	Serial.begin(74880);
	pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);             // LED is active LOW
}

void loop() {
	flashDigit(241);
}

void flashDigit(int num){
    static SimpleTimer timer1;
    static int ms = 200;
    static int flashCounter =0;
    static int arrayPointer=0;

    // Return if nothing to do; starts timer if not already running.
	if (!timer1.done(ms, 0)){ return;}

    // H,T,U and interdigit indicators
    int array[] {0, (num/100)%10, 0, (num/10)%10, 0, num %10, 0};
    
    // Array pointer is even, or zero?
    if(!(arrayPointer %2)){         // If pointer is even 0,2,4,6...
        digitalWrite(ledPin,1);     // Turn LED off
        ms = 1000;                  // for 1000ms
        ++arrayPointer %=7;         // Next array element (or wrap around to zero)
        flashCounter=0;             // Reset flash counter
        DEBUG
        return;
    }

    // Change the LED state; if flashCounter is 'even' turn off LED
    flashCounter++; 
    digitalWrite(ledPin, flashCounter %2 ? HIGH:LOW);        // Odd count = LOW (LED on)

    // If the digit value is zero
    if(0 == array[arrayPointer]){
        digitalWrite(ledPin,0);
        flashCounter = 0;
        ++arrayPointer %=7;
        ms = 1000;        
        DEBUG
        return;
    }

    // Digit value is non-zero. Either get more flashes, or get next digit
    if(flashCounter < array[arrayPointer] *2 ){
        ms = 200;
        DEBUG
    return;
    }

    else {
        ++arrayPointer %=7;
        ms=1000; 
        DEBUG
    return; }
}