/*SimpleTimer v2.0,  22 December 2021
* By Richard Langner, Sheffield, UK
* A light-weight non-blocking interrupt-free timer class.
*
* INITIALISE
* 		SimpleTimer timer1;
* 
* AUTO-REPEAT every 500ms until disabled
* 		if(timer1.event(500){...}
* 
* AUTO-REPEAT every 500ms, do this 10 times
* 		if(timer1.event(500, 10){...}
*
* SINGLE-SHOT after 500ms, do it once
* 		if(timer1.event(500, 1){...}
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
* 		c = eventCount();
*/
#ifndef SIMPLE_TIMER
#define SIMPLE_TIMER
#include <Arduino.h>

/** Timer/scheduler with millisecond accuracy */
class SimpleTimer	
{
//------------------ Private ----------------
private:
	unsigned long _setMillis=0, _prevMillis = 0;
	int  _eventCount;
	bool _enabled=true;
	bool timedOutFunction(){return (millis() - _prevMillis >= _setMillis);}
	void _start(unsigned long u){	_setMillis=u; _prevMillis=millis();}
	bool firstRun=true;

//------------------ Public -----------------
public:
// General purpose variables, free to use
int				userIntA, 	userIntB;
bool			userBoolA, 	userBoolB;
unsigned long 	userULongA,	userULongB;
virtual ~ SimpleTimer(){}

/** @param msecs milliseconds before the event returns true
*	@param cycles (optional) number of cycles required (0 means continuous)*/
bool event(unsigned long msecs, int cycles=0){
	if(!_enabled){return false;}				// Not valid timeOut
	if(!timedOutFunction()){return false;}		// Not valid timeOut
	if(cycles==0){_start(msecs);return true;}	// Continuous mode?
	if(firstRun){_start(msecs); firstRun=false; return false;}
	if(cycles > _eventCount++ ){_start(msecs);return true;}	// Valid timeOut
	_enabled=false;	
	firstRun=true;								// Sleep now ...
	return false;
}
/**	@return true if enabled */
bool enabled(){return _enabled;}

/** @param enabled Set to 'true' to enable the timer */
void enable(bool enabled=true){	_enabled=enabled; _eventCount=0; firstRun=true;}

/**	@return milliseconds since enabled, 0 if disabled */
unsigned long elapsed(){return timedOutFunction() ? 0 : millis() - _prevMillis;}

/** @return number of completed cycle events  */
int eventCount(){return _eventCount;}
};
#endif