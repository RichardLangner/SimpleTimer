/* 
Blink number, up to 5 digits, with 1 1000ms gap between each digit. Then repeats afet 2000ms.
Each flash 'on' is 200ms. A zero is 1000ms on. The flash 'off' time is 200ms.
Written by Richard Langner, Sheffield Hackspace, UK 21 April 2023.
*/

#include "SimpleTimer.h"					// Include the Timer class definition.
void flashDigit(int num);
int ledPin = D4;                            // Wemos D1 mini

void setup() {
	Serial.begin(74880);
	pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);             // LED is active LOW
}

void loop() {
	flashDigit(246);
}

void flashDigit(int num){
    static SimpleTimer timer1;
    static int ms = 200;
    static bool state = false;

	if (!timer1.done(ms, 0)){ return;}							// Return if nothing to do.

    int array[] {(0, 2*num/100)%10, 0, (2*num/10)%10, 0, 2*num%10, 0};  // H,T,U and intergroup indicator
    
    digitalWrite(ledPin, (state ? HIGH:LOW));
    

    
    //
    // Use timer1.intA  array pointer to digit value
    // Use timer1.intB  counts flashes done
    // Use timer1.longA for tick count ON (1 tick=200ms)
    // Use timer1.longB for tick count OFF

    // If  normal digit flash on/off tick=1
    switch (array[timer1.intA])
    {
    case  0 : timer1.longA = 5; timer1.longB =  1; break;   // Zero         1000ms ON,  200 ms OFF
    //
    // case 10 : timer1.longA = 0; timer1.longB =  5; break;   // Inter group     0ms ON, 1000 ms OFF
    default : timer1.longA = 1; timer1.longB =  1; break;   // Actual digit  200ms ON,  200 ms OFF
    }
    
    Serial.printf("Line %3d pointer timer1.intA = %2d, number = %d,        timer1.longA = %0.4d, timer1.longB = %0.4d\n"
                    ,__LINE__,      timer1.intA,       array[timer1.intA], timer1.longA,        timer1.longB  );
    
	if(timer1.intB < array[timer1.intA]){                       // Do more flashes?
		int odd = timer1.intA++%2;							    // odd number = LED off, then increment intA
		digitalWrite(ledPin, (odd ? HIGH:LOW));     			
        Serial.printf("Line %3d timer1.intA = %2d Led is %s \n",__LINE__, timer1.intB, odd?"High":"Low" );
		
		(array[timer1.intB] == 0) &&  !odd ? timer1.longA : timer1.longB;  	    // Long ON, short OFF
	}
	else{
		
		timer1.intA = 0;	// Get next digit - reset digit pointer					
        Serial.printf("Line %3d timer1.intA = %d\n",__LINE__, timer1.intA);		// Reset blink intA
		// Increment array pointer, wrap to 0 (adjust for supressed leading zeros).
		++timer1.intA %=3;	
        Serial.printf("Line %3d Increment array pointer to %d\n",__LINE__, timer1.intA);
	}
    return;	
}


