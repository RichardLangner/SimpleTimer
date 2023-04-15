/*
Flash a number with the built-in LED
Richard Langner, Sheffield Hackspace member, UK. 10 April 2023.
*/
#include "SimpleTimer.h"
// number to flash, pin to flash, LED active HIGH or LOW, repeats (zero for continuous)
void flashLED(int num, int LEDpin, bool onLevel, int repeat); 
const int ledPin1 = LED_BUILTIN;

void setup() {
  pinMode(ledPin1, OUTPUT); 
    Serial.begin(74880);
}

void loop() {
flashLED(402, ledPin1, LOW, 0);
}

void flashLED(int num, int LEDpin, bool active, int repeats=0){
    static SimpleTimer t1;
    int array[] {(num/100)%10, (num/10)%10, num%10};
    unsigned long gapArray[] {1000, 200, 200, 3000};
    unsigned long ms;
    // t1.intA is the counter of flashes required
    // t1.intB : 0= interdigit gap, 1= mark, 2= space, 3= intergroup gap.
    // t1.intB is the digit position
    // t1.boolA determines whether mark or space

    switch (t1.intB)
    {
        case 0: // interdigit gap
            /* code */
            break;
        case 1: // mark
            if(!t1.done(200)) {
                digitalWrite(LEDpin, active);
            }
            break;
        case 2: // space
            if(!t1.done(200)) {
                digitalWrite(LEDpin, !active);
            break;
        case 3: // intergroup gap
            /* code */
            break;
        default:
            break;
    }

    if(t1.boolA){
        // Code to handle zero as a single long flash
        // if zero make it a 600ms ON
        if(array[t1.intB] == 0 && !(t1.intA % 2)){
            ms=1000; array[t1.intB] = 1; // Change 0 to 1 and extend the on time
            // Serial.printf("Line %2d ms= %3u array[t1.intB]= %3d\n",__LINE__, ms, array[t1.intB]);
            if(!t1.boolB){
                // Set zero flag to only enable once
                Serial.printf("Line %2d\n",__LINE__);
                t1.boolB = true;
                t1.enabled();
            }
        }
        else 
        ms=200;

        if(ms==1000){Serial.printf("Line %2d ms=1000 millis = %6lu\n", __LINE__, millis());}

        if(t1.done(ms, array[t1.intB]*2)){
            // turn LED on/off if count is ODD/EVEN
            digitalWrite(LEDpin, !active ^ !(t1.intA % 2));  
            // intA is the number of flashes for the digit     
            t1.intA ++;
            Serial.printf("Line %2d array[%d] = %d t1.intA = %d\n", __LINE__, t1.intB, array[t1.intB], t1.intA);
            }

        if(t1.intA== (array[t1.intB]*2)){   // Have done all the flashes for the current digit?
            t1.intA=0;                      // Reset flash counter
            t1.intB++;                      // Go to next digit
            if(t1.intB > 2){t1.intB=0;}     // Don't go higher than digits 0 to 2
            t1.boolB=false;                 // Reset zero flag
            t1.boolA=false;                 // Reset mark:space to space
        }
    }
    else{
        if(t1.done(700)){
            // Turn off the LED during the interdigit pause
            digitalWrite(LEDpin, !active ^ (t1.intA % 2));
            t1.boolA=true;
            t1.enabled();
            Serial.printf("Line %2d timer1.intB= %d\n", __LINE__, t1.intB);
        }
    }

}
