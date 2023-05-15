/* 
Blink (up to) a 5 digit number on a single LED. 500ms gap between each digit.
Repeats after 3000ms. Returns 'true' when it completes a group of digits.
The flash 'on' and 'off' period is 200ms each. A zero is 1000ms 'on'.
Interdigit gap is defined by a negative number of ms.
Written by Richard Langner, Sheffield Hackspace, UK 15 May 2023.
Latest code on github.com/RichardLangner/SimpleTimer
*/
#ifndef FLASHNUMBER
#define FLASHNUMBER
#include <Arduino.h>

#include "SimpleTimer.h"
#define DEBUG Serial.printf("%3d After %4d ms of LED %s, P=%d, digit=%d, F=%d, offset=%d\n", __LINE__, ms, digitalRead(ledPin) ? "Off":"On ", arrayPointer, array[arrayPointer], flashCounter, offset);
#define DEBUG2 Serial.printf("%3d LED=%s\n", __LINE__, digitalRead(ledPin) ? "Off":"On ");

/** @return - true if all the digits have been flashed.
*	@param num number to flash, max 99999.
*	@param wide number of digit places to flash, 0 means automatic with no leading zeros.
*   @param ledPin GPIO port number of the LED.
*   @param activeLevel logic level required for LED to be on.
*/

bool flashNumber(int num, int wide, int ledPin, int activeLevel){
    static SimpleTimer timer1;
    static int ms = 10;
    static int flashCounter =0;
    static int arrayPointer;
    static int offset;

    // Return if nothing to do; starts timer if not already running.
	if (!timer1.done(ms, 0)){return false;}
    // Validate arguments
    if(num <0 or wide <0 or wide >5) {return false;}

    // Digit values and interdigit times
    int array[] {-500, (num/10000)%10, -500, (num/1000)%10,-500, (num/100)%10, -500, (num/10)%10, -500, num %10, -2500};

    // Calculate the offset array position to start at
    if(wide==0){offset= 10-(2 * ((int)log10(num) +1));} else {offset = 10 - 2*wide;}DEBUG

    if(arrayPointer==0) {arrayPointer= offset;}
    
    // Gaps between digits
    if(array[arrayPointer] < 0){                // Inter-digit gap (as it's a minus value)
        digitalWrite(ledPin,1);                 // Turn LED off
        ms = -array[arrayPointer];              // Make value positive
        flashCounter=0; ++arrayPointer %=11;    // Next array element (or wrap around to zero)
        if(arrayPointer==0) {arrayPointer= offset; return true;}
        return false;
    }

    // Change the LED state; if flashCounter is 'even' turn off LED
    flashCounter++; 
    digitalWrite(ledPin, flashCounter %2 ? LOW :HIGH);  // Odd count = LOW (LED on)

    // If the digit value is zero
    if(0 == array[arrayPointer]){
        digitalWrite(ledPin,0);
        ms = 1000;
        flashCounter = 0; ++arrayPointer %=11;
        if(arrayPointer==0) {arrayPointer= offset; return true;}
        return false;
    }

    // Digit value is non-zero. Either get more flashes, or get next digit
    if(flashCounter < array[arrayPointer] *2 ){
        ms = 200;
    return false;
    } else {  // Get next digit
        flashCounter = 0; ++arrayPointer %=11;
        if(arrayPointer==0) {arrayPointer= offset; return true;}  
        return false; 
    }
}
#endif