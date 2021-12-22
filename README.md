# SimpleTimer

* Auto repeat
* Multiple shot and Single shot
* Enable/disable
* Auto-starts when enabled
* Non-blocking code does not slow your program
* Does not require interrupts, works on any GPIO pin
* Schedule functions, to  run one or more times
## WHO NEEDS NEED IT?
If you want to blink an LED, refresh an LCD or regularly read sensors, this is for you.
## AUTO-REPEAT<br>
To run code every 500ms<br>
* `if(timer1.event(500){...}`<br>
## MULTIPLE AND SINGLE-SHOT
Multiple-shot : To run code every 500ms, but only run it 10 times<br>
* `if(timer1.event(500, 10){...}`

Single-shot : To run code once after a 500ms delay, use a repeat of 1<br>
* `if(timer1.event(500, 1){...}`<br>

## ENABLE/DISABLE ( START-STOP )
To start a SimpleTimer if it was previously stopped (resets cycle count)<br>
* `timer1.enabled(true);`<br>

To stop a SimpleTimer if it's running (resets cycle count)<br>
* `timer1.enabled(false);`

To check if a SimpleTimer is enabled and running<br>
* `if(timer1.enabled()){...}`<br>
## ELAPSED TIME
To get the time (ms) a SimpleTimer has been running during a timing period

* `t = timer1.elapsed();`<br>
## CYCLE COUNT
When using Multiple-shot, it returns the number of completed time-outs. In auto-repeat mode it returns zero.
* `c = cycleCount();`<br><br>
# EXAMPLE CODE
The examples in the `SimpleTimer examples` folder use the board's LED_BUILTIN to demonstrate most of SimpleTimer's features.
## FLASHING AN LED
Flashing an LED is simple. It starts automatically, and you can stop/start it<br>
* `if(timer1.event(250) ){`<br>
`digitalWrite(ledPin1, !digitalRead(ledPin1));`<br>
`}`<br>

To stop the flashing
* `timer1.enabled(false)`

To restart the flashing
* `timer1.enabled(true)`

## FLASHING AN LED - SINGLE OR MULTIPLE TIMES
A single flash has 2 transitions, on and off<br>
* `if(timer1.event(250,2) ){`<br>
`digitalWrite(ledPin1, !digitalRead(ledPin1));`<br>
`}`

Five flashes have 10 transitions<br>
* `if(timer1.event(250,10) ){`<br>
`digitalWrite(ledPin1, !digitalRead(ledPin1));`<br>
`}`<br>

## FLASHING AN LED - DIFFERENT ON/OFF TIMES
To flash the LED asymmetrically (on 600ms, off 100ms), see the example code in `Blink asymmetrical.cpp` The function call is 
* `switchOnOff(600,100);`
## HEARTBEAT
The example `Blink heartbeat.cpp` shows an alternative to using a PWM pin to make the LED glow and dim. The function call is<br>
 * `heartbeat();`