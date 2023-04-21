/* 
Wemos D1 mini IO test LED board v0.02.
Written by Richard Langner, Sheffield Hackspace, UK 20 April 2023.
*/

#include "SimpleTimer.h"					// Include the Timer class definition.
// SimpleTimer timer1;
void flashDigit(int num);
int ledPin = D4;

uint8_t digitArray [] {6,20,6,2,4};	// E.g. double 192 for mark-space, max int is 5 digits (max 65535). zero should be 1.

int digitArrayPointer = 0;

void setup() {
	Serial.begin(74880);
	pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);             // LED is active LOW
	// timer1.done(5000);					// Start with a 100ms pause.
}

void loop() {
	flashDigit(5);
}

void flashDigit(int num){
    static SimpleTimer timer1;
	if (!timer1.done(200, 0)){ return;}							// Return if nothing to do.

    int array[] {(2*num/100)%10, (2*num/10)%10, 2*num%10, -1};  // H,T,U and intergroup indicator

    // Use timer1.intA for digit value
    // Use timer1.intB for flasher counter
    // Use timer1.longA for tick count ON (1 tick=200ms)
    // Use timer1.longB for tick count OFF

    // If  normal digit flash on/off tick=1
    switch (array[timer1.intA])
    {
    case  0 : timer1.longA = 5; timer1.longB =  1; break;   // Zero         1000ms ON, 200  ms OFF
    case -1 : timer1.longA = 0; timer1.longB = 15; break;   // Inter digit     0ms ON, 1000 ms OFF
    default : timer1.longA = 1; timer1.longB =  1; break;   // Actual digit  200ms ON, 200  ms OFF
    }

    if(array[timer1.intB] > 0) {timer1.longA = 1; timer1.longB = 1;
    }


	if(timer1.intA < array[timer1.intB]){                       // Do more flashes?
		int odd = timer1.intA++%2;							    // odd number = LED off, then increment intA
		digitalWrite(ledPin, (odd ? HIGH:LOW));     			
        Serial.printf("Line %3d timer1.intA = %2d Led is %s \n",__LINE__, timer1.intA, odd?"High":"Low" );
		
		(array[timer1.intB] == 0) &&  !odd ? 2000 : 200;  	    // Long ON, short OFF
        // int y = (digit == 20) && !odd ? 2000 : 200; Serial.printf("Line %3d delay = %d\n",__LINE__, y);	
		// if(digit==20 &&  !odd){timer1.intA=19;}
	}
	else{
		// Get next digit
		timer1.intA = 0;										
        Serial.printf("Line %3d timer1.intA = %d\n",__LINE__, timer1.intA);		// Reset blink intA
		// Increment array pointer, wrap to 0 after 4. Start timer.
		timer1.done((++digitArrayPointer %=5) ? 1000:3000);	
        Serial.printf("Line %3d Increment array pointer to %d, and start %dms delay\n",__LINE__, digitArrayPointer,(digitArrayPointer ? 1000:5000));
	}
	
	return;	
}


