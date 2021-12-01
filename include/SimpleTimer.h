/*SimpleTimer v1.0,  27 November 2021
* By Richard Langner, Sheffield, UK
* A light-weight non-blocking interrupt-free timer class.
* 
* AUTO-REPEAT every 500ms
* 		if(timer1.timedOut(500){...}
* 
* AUTO-REPEAT every 500ms, do this 10 times
* 		if(timer1.timedOut(500, 10){...}
* 
* ENABLE
* 		timer1.enabled(true);
* 		timer1.enabled(false);
* 		if(timer1.enabled()){...}
* 
* TIME ELAPSED
* 		t = timer1.elapsed();
* 
* AUTO-REPEATS COMPLETED (zero if continuous)
* 		c = cycleCount();
*/
#ifndef SIMPLE_TIMER
#define SIMPLE_TIMER
#include <Arduino.h>

class SimpleTimer	
{
//------------------ Private ----------------
private:
	unsigned long setMillis=0, prevMillis = 0;
	int timedOutFlag, _cycleCount;
	bool _enabled=true;
	bool timedOutFunction(){return (millis() - prevMillis >= setMillis);}
	void start(unsigned long u = 1000){	setMillis=u; prevMillis=millis(); _enabled=true;}

//------------------ Public -----------------
public:
// General purpose variables, free to use
int				userIntA, 	userIntB;
bool			userBoolA, 	userBoolB;
unsigned long 	userULongA,	userULongB;
virtual ~ SimpleTimer(){}

bool timedOut(unsigned long msecs, int cycles=0){
	if(!_enabled){return false;}							// Not valid timeOut
	if(!timedOutFunction()){return false;}					// Not valid timeOut
	if(cycles==0){start(msecs);return true;}				// Continuous mode?
	if(cycles > _cycleCount++ ){start(msecs);return true;}	// Valid timeOut
	_enabled=false;											// Sleep now ...
	return false;
}

bool enabled(){return _enabled;}

void enabled(bool enabled){	_enabled=enabled; _cycleCount=0;}

unsigned long elapsed(){return timedOutFunction() ? 0 : millis() - prevMillis;}

int cycleCount(){return _cycleCount;}
};
#endif