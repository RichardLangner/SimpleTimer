# SimpleTimer

* Continuous / Multiple shot / Single shot
* Disable/enable
* Run many SimpleTimers simultaneously
* Schedule functions to run one or more times
* Non-blocking code does not slow your program
* Tiny code footprint, no interrupts used
## WHO NEEDS NEED IT?
If you just want to blink an LED, or refresh an LCD or regularly read sensors, this is for you.
## AUTO-REPEAT<br>
To run code every 500ms<br>
* `if(timer1.done(500){...}`<br>
## MULTIPLE AND SINGLE-SHOT
Multiple-shot : To run code every 500ms, but only run it 10 times<br>
* `if(timer1.done(500, 10){...}`

Single-shot : To run code once after a 500ms delay, use a repeat of 1<br>
* `if(timer1.done(500, 1){...}`<br>

## ENABLE/DISABLE ( START/STOP )
To start a SimpleTimer if it was previously stopped<br>
* `timer1.enabled(true);`<br>

To stop a SimpleTimer if it's running<br>
* `timer1.enabled(false);`

To check if a SimpleTimer is enabled and running<br>
* `if(timer1.isEnabled()){...}`<br>
## ELAPSED TIME
To get the time (ms) a SimpleTimer has been running during a timing period

* `t = timer1.elapsed();`<br><br>
# EXAMPLE CODE
The code in the `SimpleTimer_examples` folder use the board's LED_BUILTIN to demonstrate most of SimpleTimer's features. Simply paste the code into your 'main.c' or '.ino' file. and ensure the SimpleTimer header is an 'include' file.
## Blink_simple.cpp
Flashing an LED continuously is simple, here it's 250ms on and 250ms off (2Hz)<br>
* `if(timer1.done(250) ){`<br>
`digitalWrite(ledPin1, !digitalRead(ledPin1));`<br>
`}`<br>

To stop the flashing
* `timer1.enabled(false)`

To restart the flashing
* `timer1.enabled(true)`

## Blink_5_then_stop.cpp
* Flashes LED 5 times, then stops<br>
## Blink_5_repeating.cpp 
* Flashes LED 5 times, repeats after a pause<br>
## Blink_asymmetrical.cpp
* Flashes an LED with different on/off periods
## Heartbeat_gentle_fade.cpp
* Makes the LED glow and dim slowly.
## Heartbeat_pulse_fade.cpp
* Turns LED on fast then dims it slowly
## Startup scheduler.cpp
* Runs various functions at various times after start-up