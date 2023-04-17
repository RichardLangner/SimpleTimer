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
flashLED(206, ledPin1, LOW, 0);
}

void flashLED(int num, int LEDpin, bool active){
    #define digit_gap    1000            // Pause between each digit
    #define group_gap_ms    4000            // Pause between each group of digits
    #define mark_space_ms   200             // On and off times for each flash
    #define zero         900
    // Defines below make the code more readable.
    // They point to internal variables of SimpleTimer that are available to the user.
    #define flashes         timer.intA      // The number of flashed completed for a digit  
    #define digit           timer.intB      // Pointer to the array of 3 digits
    #define digitGap        timer.boolA     // True when gap required between digits
    #define msec            timer.longA     // Sets times of SPACE ON, inter-digit and inter-group
    #define DEBUG Serial.printf("Line %2d digit= %d, mode = %d, %s\n", __LINE__, digit, mode, digitalRead(ledPin1) ? "Off" : "On");
    static SimpleTimer timer;
    static int array[] {(num/100)%10, (num/10)%10, num%10};

<<<<<<< HEAD

    if(msec == space_ms){
        if( !timer.done(space_ms )) { digitalWrite(LEDpin, active); }
        else { timer.enabled(true); msec = digit_gap_ms; }
        return;    
    }

    if(msec == digit_gap_ms) {
        if( !timer.done(digit_gap_ms )) { digitalWrite(LEDpin, !active); }
        else { timer.enabled(true); msec = 0; }
=======
    if(msec == zero){
        if( !timer.done(zero )) { digitalWrite(LEDpin, active); }
        else { timer.enabled(true); msec = digit_gap; }
        // Serial.printf("Line: %3d\n",__LINE__);
        return;    
    }

    if(msec == digit_gap) {      // Gap between groups of 3 digits
        if( !timer.done(digit_gap )) { digitalWrite(LEDpin, !active); }
        else { 
            timer.enabled(true);
            digit = (++digit) % 3;
            msec = 0;}
>>>>>>> b4a34de8590e83dcfc17421facc55448ea7969ac
        return;
    }


    // if(digit == 3){
    //     digitalWrite(LEDpin, !active);      // Turn off the LED between each group of numbers
    //     if(timer.done(ms_Group_gap)){
    //         digit = 0;
    //         // Serial.printf("Line %2d digit= %d, LED= %s\n", __LINE__, digit, digitalRead(ledPin1) ? "Off" : "On");
    //         timer.enabled(true);            // Get ready for next timer use
    //     }
    //     return;
    // }
    
    if(array[digit] == 0){                  // Check if digit is zero and give a long flash
    // ******* ADD AN 'OFF' DELAY
        msec = space_ms;

    }

    if(msec == 0){
<<<<<<< HEAD
=======
        if(array[digit] == 0){
            msec = zero;
            timer.enabled(true); 
            return;
        }
>>>>>>> b4a34de8590e83dcfc17421facc55448ea7969ac
        if(timer.done(mark_space_ms, (array[digit] * 2))){
            digitalWrite(LEDpin, active ^ (flashes % 2));   // Toggles the LED, 'flashes' even = OFF, odd = ON
            // Serial.printf("Line %2d digit= %d, flashes= %d, %s\n", __LINE__, digit, flashes, digitalRead(ledPin1) ? "Off" : "On");
            flashes++;
        }
        if(flashes == array[digit] * 2){        // Get next digit
<<<<<<< HEAD
            flashes = 0;
            digit++;
            digitGap = true;                    // Set flag for inter-digit gap timer
=======
            Serial.printf("Line %2d digit= %d, flashes= %d\n", __LINE__, digit, flashes);
            flashes = 0;
            // digit = (++digit) % 3;
            msec = digit_gap;
>>>>>>> b4a34de8590e83dcfc17421facc55448ea7969ac
            timer.enabled(true);                // Get ready for next timer use
            // Serial.printf("Line %2d digit= %d, flashes= %d\n", __LINE__, digit, flashes);
        }
    return;
    }
}
