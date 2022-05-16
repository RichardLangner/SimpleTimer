# SimpleTimer
## Simplify common tasks e.g.
* Refresh an LCD or OLED every 500ms
* Read sensors every few minutes
* Flash an LED a preset number of times
* Heartbeat LED
## Features
* Repeating / Multiple shot / Single shot timing
* Disable/enable
* Timing progress monitor
## Advantages
* Simplifies your code
* Multiple SimpleTimers can run simultaneously
* Schedules functions to run one or more times
* Tiny code footprint, non-blocking, no interrupts used
# How do I use it?
## Auto-repeat, for repetitive tasks<br>
To run code every 500ms<br>
* `if(timer1.done(500){...}`<br>
## Multiple and single-shot
Multiple-shot : To run code every 500ms, but only run it 10 times<br>
* `if(timer1.done(500, 10){...}`

Single-shot : To run code once after a 500ms delay, use a repeat of 1<br>
* `if(timer1.done(500, 1){...}`<br>

## Enable/disable (start/stop)
To prevent a SimpleTimer from running<br>
* `timer1.enabled(false);`

To restart a SimpleTimer<br>
* `timer1.enabled(true);`

To check if a SimpleTimer is enabled and running<br>
* `if(timer1.isEnabled()){...}`<br>
## Elapsed time (progress monitor)
To get the time (ms) a SimpleTimer has been running during a timing period

* `t = timer1.elapsed();`<br><br>
# EXAMPLE CODE
The code in the `SimpleTimer_examples` folder uses the board's LED_BUILTIN to demonstrate most of SimpleTimer's features. Simply paste the code into your 'main.c' or '.ino' file and ensure the SimpleTimer header is an 'include' file.
## Blink_simple.cpp
Flashing an LED continuously is simple, here it's 250ms on and 250ms off (2Hz)<br>


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
* Runs various functions at various times after start-up, in this example it writes to the serial port