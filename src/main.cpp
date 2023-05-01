/* 
Blink number, up to 5 digits, with a 1000ms gap between each digit. Then repeats afet 2000ms.
The flash 'on' and 'off' period is 200ms each. A zero is 1000ms on.
Written by Richard Langner, Sheffield Hackspace, UK 1 May 2023.
*/

#include "SimpleTimer.h"					// Include the Timer class definition.
void flashDigit(int num, int pad);
int ledPin = D4;                            // Wemos D1 mini LED pin
#define DEBUG Serial.printf("%3d After %4d ms of LED %s, P=%d, digit=%d, F=%d\n", __LINE__, ms, digitalRead(ledPin) ? "Off":"On ", arrayPointer, array[arrayPointer], flashCounter);
#define DEBUG2 Serial.printf("%3d LED=%s\n", __LINE__, digitalRead(ledPin) ? "Off":"On ");

void setup() {
	Serial.begin(74880);
	pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);             // LED is active LOW
}

void loop() {
	flashDigit(5,3);
}

void flashDigit(int num, int pad){
    static SimpleTimer timer1;
    static int ms = 300;
    static int flashCounter =0;
    static int arrayPointer=0;

    // Return if nothing to do; starts timer if not already running.
	if (!timer1.done(ms, 0)){ return;}
    
    // H,T,U and interdigit indicators
    int array[] {-500, (num/100), -500, (num/10)%10, -500, num %10, -2000};
    Serial.printf("Num= %d%d%d\n",array[1],array[3],array[5]);
    DEBUG

    int offset = 6 - 2*pad;
    // Array pointer is even, or zero?
    if(array[arrayPointer] < 0){    // Inter-digit gap (it's a minus value)
        digitalWrite(ledPin,1);  DEBUG2    // Turn LED off
        ms = -array[arrayPointer];  // Make value positive
        ++arrayPointer %=7;         // Next array element (or wrap around to zero)
        if(arrayPointer==0) {arrayPointer= offset;}
        flashCounter=0;             // Reset flash counter
       
        return;
    }

    // Change the LED state; if flashCounter is 'even' turn off LED
    flashCounter++; 
    digitalWrite(ledPin, flashCounter %2 ? LOW :HIGH);        // Odd count = LOW (LED on)
    DEBUG2

    // If the digit value is zero
    if(0 == array[arrayPointer]){
        digitalWrite(ledPin,0);
        flashCounter = 0;
        ++arrayPointer %=7;
        if(arrayPointer==0) {arrayPointer= offset;}
        ms = 1000;
        return;
    }

    // Digit value is non-zero. Either get more flashes, or get next digit
    if(flashCounter < array[arrayPointer] *2 ){
        ms = 200;
        DEBUG2
    return;
    } else {  // Get next digit
        ++arrayPointer %=7;
        if(arrayPointer==0) {arrayPointer= offset;}
        flashCounter = 0;
        DEBUG2
    return; }
}