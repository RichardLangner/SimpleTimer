/* 
Blink (up to) a 5 digit number on a single LED. 500ms gap between each digit.
Repeats after 3000ms. Returns 'true' when it completes a group of digits.
The flash 'on' and 'off' period is 200ms each. A zero is 1000ms 'on'.
Interdigit gap is defined by a negative number of ms.
Written by Richard Langner, Sheffield Hackspace, UK 21 May 2023.
Latest code and examples on github.com/RichardLangner/SimpleTimer
*/
#ifndef FLASHNUMBER
#define FLASHNUMBER
#include <Arduino.h>
#include "SimpleTimer.h"

/** @return - true if all the digits have been flashed.
*	@param num number to flash, max 99999.
*   @param ledPin GPIO port number of the LED.
*   @param LED_on logic level required for LED to be on.
*	@param width (opional) number of digit places to flash. If not specified, or zero, means with no leading zeros.
*/

class FlashDigits
{
private:
bool    _enabled=true;
int     _ledPin, _led_on;
SimpleTimer timer1;
int ms = 10, flashCounter =0, arrayPointer, offset;
int array[11] = {-500,0,-500,0,-500,0,-500,0,-500,0,-2500};

public:
virtual ~ FlashDigits(){}

    bool flash(int num, int ledPin, bool LED_on, int width=0){
        // Exit if disabled
        if(!_enabled){return false;}
        // Return if nothing to do; starts timer if not already running.
        if (!timer1.done(ms, 0)){return false;}
        // Validate arguments
        if(num <0 or width <0 or width >5) {return false;}

        if(arrayPointer==0){
            // Digit values and interdigit times
            // array[1] = (num/10000)%10;
            // array[3] = (num/1000)%10;
            // array[5] = (num/100)%10;
            // array[7] = (num/10)%10;
            // array[9] =  num %10;

            for(int ii = 1, divisor = 10000; ii < 10; ii += 2, divisor /= 10){
                array[ii] = (num / divisor) % 10;
            }

            // Calculate the offset array position to start at
            if(width==0){offset= 10-(2 * ((int)log10(num) +1));} else {offset = 10 - 2*width;}
            arrayPointer= offset;
        }
        
        // Gaps between digits (indicated by a minus value)
        if(array[arrayPointer] < 0){                // Check if minus
            digitalWrite(ledPin, !LED_on);          // Turn LED off
            ms = -array[arrayPointer];              // Make gap value positive
            flashCounter=0; ++arrayPointer %=11;    // Next array element (or wrap around to zero)
            if(arrayPointer==0) {return true;}
            return false;
        }

        // Change the LED state; if flashCounter is 'even' turn off LED
        flashCounter++; 
        digitalWrite(ledPin, flashCounter %2 ? LED_on : !LED_on);  // Odd count = on

        // If the digit value is zero
        if(0 == array[arrayPointer]){
            digitalWrite(ledPin,LED_on);
            ms = 1000;
            flashCounter = 0; ++arrayPointer %=11;
            if(arrayPointer==0) {return true;}
            return false;
        }

        // Digit value is non-zero. Either get more flashes, or get next digit
        if(flashCounter < array[arrayPointer] *2 ){ms = 200; return false;
        } else {  // Get next digit
            flashCounter = 0; ++arrayPointer %=11;
            if(arrayPointer==0) {return true;}  
            return false; 
        }
    }

/**	@return 'true' if the flasher is enabled */
    bool enabled(){return _enabled;}
/** @param enabled 'true' enables, 'false' disables the flasher */   
    void enabled(bool enabled){_enabled=enabled;}

/** @return Nothing returned
    @param  ledPin the LED pin number
    @param  level logic level to turn on the LED**/
    void setup(int ledPin, int led_on){
        _ledPin=ledPin; _led_on=led_on;
    }   
};
#endif