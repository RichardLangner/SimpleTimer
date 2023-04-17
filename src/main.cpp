/*
Flash a three digit number with the built-in LED
Ideal for informing of the last wifi IP number xxx e.g. 192.168.1.xxx
Richard Langner, Sheffield Hackspace member, UK. 14 April 2023
*/
#include "SimpleTimer.h"
// #include <stdarg.h>

// Number to flash, pin to flash, LED active HIGH or LOW, repeats (zero for continuous).
// Returns the number of completed groups.
void flashLED(int num, int LEDpin, bool onLevel); 

const int ledPin1 = LED_BUILTIN;

void setup() {
    pinMode(ledPin1, OUTPUT); 
    Serial.begin(74880);
    Serial.printf("Line %2d\n", __LINE__);
}

void loop() {
flashLED(216, ledPin1, HIGH);
}

void flashLED(int num, int LEDpin, bool active){
    #define digit_gap_ms    2000            // Pause between each digit
    #define group_gap_ms    4000            // Pause between each group of digits
    #define mark_space_ms   200             // On and off times for each flash
    #define space_ms         1000
    // Defines below make the code more readable.
    // They point to internal variables of SimpleTimer that are available to the user.
    #define flashes         timer.intA      // The number of flashed completed for a digit  
    #define digit           timer.intB      // Pointer to the array of 3 digits
    #define digitGap        timer.boolA     // True when gap required between digits
    #define msec            timer.longA     // Sets times of SPACE ON, inter-digit and inter-group
    #define DEBUG Serial.printf("Line %2d digit= %d, mode = %d, %s\n", __LINE__, digit, mode, digitalRead(ledPin1) ? "Off" : "On");
    static SimpleTimer timer;
    static int array[] {(num/100)%10, (num/10)%10, num%10};
    static int mode = 0;
    // static ulong ms;
    // static bool ledState = false;
    static int flashCount = 0;

    switch (mode)
    {
    case 0: // Inter-group :  arrives LED OFF, then turned ON after 3000ms
        if(timer.done(3000)) {digitalWrite(LEDpin, active); timer.enabled(true); mode = 1; DEBUG
        } return;
    
    case 1: // Zero long ON : arrives LED ON, then turned OFF after 1000ms
         if(array[digit] == 0) {if(timer.done(1000)) { digitalWrite(LEDpin, !active); timer.enabled(true); mode = 0; DEBUG}
         } else {mode = 2;DEBUG} return;  
    
    case 2: // Flash : arrives LED ON, turns OFF after 200ms
        if(timer.done(200)) {digitalWrite(LEDpin, !active); timer.enabled(true); ++flashCount; DEBUG}
            if(flashCount == array[digit]){ // Done enough flashes?
                flashCount=0; ++digit;   DEBUG   // Get next digit
                if(digit==3){     DEBUG          // Start again at first digit
                    digit=0; mode=0; DEBUG return;
                }
                mode=4;     DEBUG                // Inter-digit gap
            }
         return;

    case 3: // Flash : arrives LED OFF, turns ON after 200ms
        if(timer.done(200)) {digitalWrite(LEDpin, active); timer.enabled(true); mode = 2;DEBUG} return;
    
    case 4: // Inter-digit : arrives LED OFF, turns ON after 1000ms
        if( timer.done(1000)) {digitalWrite(LEDpin, active); timer.enabled(true); mode = 1; DEBUG} return;
    }

}
