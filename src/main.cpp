/*
Flash a three digit number with the built-in LED
Ideal for informing of the last wifi IP number xxx e.g. 192.168.1.xxx
Richard Langner, Sheffield Hackspace member, UK. 14 April 2023
*/
#include "SimpleTimer.h"
#include <stdarg.h>
// Number to flash, pin to flash, LED active HIGH or LOW, repeats (zero for continuous).
// Returns the number of completed groups.
void flashLED(int num, int LEDpin, bool onLevel); 

const int ledPin1 = LED_BUILTIN;

void setup() {
    pinMode(ledPin1, OUTPUT); 
    Serial.begin(74880);
}

void loop() {
flashLED(206, ledPin1, LOW);
}

void flashLED(int num, int LEDpin, bool active){
    #define digit_gap_ms    1000            // Pause between each digit
    #define group_gap_ms    4000            // Pause between each group of digits
    #define mark_space_ms   200             // On and off times for each flash
    #define zero_ms         900
    // Defines below make the code more readable.
    // They point to internal variables of SimpleTimer that are available to the user.
    #define flashes         timer.intA      // The number of flashed completed for a digit  
    #define digit           timer.intB      // Pointer to the array of 3 digits
    #define digitGap        timer.boolA     // True when gap required between digits
    #define msec            timer.longA     // Sets times of SPACE ON, inter-digit and inter-group

    static SimpleTimer timer;
    static int array[] {(num/100)%10, (num/10)%10, num%10};

    if(msec == zero_ms){
        if( !timer.done(zero_ms )) { digitalWrite(LEDpin, active); }
        else { timer.enabled(true); msec = digit_gap_ms; }
        // Serial.printf("Line: %3d\n",__LINE__);
        return;    
    }

    if(msec == digit_gap_ms) {      // Gap between groups of 3 digits
        if( !timer.done(digit_gap_ms )) { digitalWrite(LEDpin, !active); }
        else { 
            timer.enabled(true);
            digit = (++digit) % 3;
            msec = 0;}
        return;
    }

    if(msec == 0){
        if(array[digit] == 0){
            msec = zero_ms;
            timer.enabled(true); 
            return;
        }
        if(timer.done(mark_space_ms, (array[digit] * 2))){
            digitalWrite(LEDpin, active ^ (flashes % 2));   // Toggles the LED, 'flashes' even = OFF, odd = ON
            // Serial.printf("Line %2d digit= %d, flashes= %d, %s\n", __LINE__, digit, flashes, digitalRead(ledPin1) ? "Off" : "On");
            flashes++;
        }
        if(flashes == array[digit] * 2){        // Get next digit
        
            Serial.printf("Line %2d digit= %d, flashes= %d\n", __LINE__, digit, flashes);
            flashes = 0;
            // digit = (++digit) % 3;
            msec = digit_gap_ms;
            timer.enabled(true);                // Get ready for next timer use
        }
    return;
    }
}
