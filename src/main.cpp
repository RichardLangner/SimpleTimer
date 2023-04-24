/* 
Blink number, up to 5 digits, with 1 1000ms gap between each digit. Then repeats afet 2000ms.
Each flash 'on' is 200ms. A zero is 1000ms on. The flash 'off' time is 200ms.
Written by Richard Langner, Sheffield Hackspace, UK 23 April 2023.
*/

#include "SimpleTimer.h"					// Include the Timer class definition.
void flashDigit(int num);
int ledPin = D4;                            // Wemos D1 mini
int flashCounter =0;
int arrayPointer=0;

void setup() {
	Serial.begin(74880);
	pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);             // LED is active LOW
}

void loop() {
	flashDigit(135);
}

void flashDigit(int num){
    static SimpleTimer timer1;
    static int ms = 200;

	if (!timer1.done(ms, 0)){ return;}							// Return if nothing to do; starts timer if not running.

    int array[] {0, (num/100)%10, 0, (num/10)%10, 0, num %10, 0};  // H,T,U and interdigit indicator

    if(!(arrayPointer %2)){       // Gap between digits and a start
        digitalWrite(ledPin,1); // Turn off LED if array pointer is zero or even
        ms = 1000;
        ++arrayPointer %=7;
        flashCounter=0;
        return;
    }
    
    digitalWrite(ledPin, (!((flashCounter) %2) ? HIGH:LOW));        // Odd count = LOW (LED on)
    flashCounter++; Serial.printf("%3d arrayPointer = %2d, num = %d, ms = %3d, flashCounter = %d\n", __LINE__, arrayPointer, array[arrayPointer], ms, flashCounter);

    // If the digit value is zero
    if(0 == array[arrayPointer]){
        ms = 1000;
        if(!flashCounter %2){            // If even (LED was off)
            (++arrayPointer)  %=7;       // Reset
            flashCounter = 0;
        }
        Serial.printf("%3d arrayPointer = %2d, num = %d, ms = %2d, flashCounter = %d\n", __LINE__, arrayPointer, array[arrayPointer], ms, flashCounter);
        return;
    }

    // Digit is non-zero. Do we need more flashes?
    if(flashCounter < array[arrayPointer] *2 ){
    ms = 200;
    Serial.printf("%3d arrayPointer = %2d, num = %d, ms = %3d, flashCounter = %d\n", __LINE__, arrayPointer, array[arrayPointer], ms, flashCounter);
    return;
    } 
    else
    {
         ++arrayPointer %=7;
    return;
    }
}