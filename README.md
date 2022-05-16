# SimpleTimer
## Typical uses
* Refresh an LCD or OLED every 500ms
* Read sensors every few minutes
* Flash an LED continuously, or a preset number of times
* Heartbeat LED
* Anywhere you need millisecond timing...
## Features
* Repeating / Multiple shot / Single shot timing
* Disable/enable
* Timing progress monitor
## Advantages
* Simplifies your code
* Multiple SimpleTimers can run simultaneously
* Schedules functions to run one or more times
* Tiny code footprint, non-blocking, no interrupts used
# HOW DO I USE IT?
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

To check if a SimpleTimer is enabled<br>
* `if(timer1.isEnabled()){...}`<br>
## Elapsed time (progress monitor)
Returns the time (ms) a SimpleTimer has been running during a timing period

* `unsigned int t = timer1.elapsed();`<br><br>
# EXAMPLE CODE
The code in the `SimpleTimer_examples` folder uses the board's LED_BUILTIN to demonstrate most of SimpleTimer's features. Simply paste the code into your 'main.c' or '.ino' file and ensure the SimpleTimer header is an 'include' file.
## Blink_simple.cpp
* Flashing an LED continuously is simple, here it's 250ms on and 250ms off (2Hz)<br>`if(timer1.done(250)){digitalWrite(ledPin1,!digitalRead(ledPin1));`
## Blink_5_then_stop.cpp
* Flashes LED 5 times, then stops<br>
`if(timer1.done(200,10)){digitalWrite(ledPin1, !digitalRead(ledPin1));`
## Blink_5_repeating.cpp
* Flashes LED 5 times, repeats every 5 seconds<br>
`if(timer1.done(200,10)){digitalWrite(ledPin1,!digitalRead(ledPin1));}
if(timer2.done(5000)){timer1.enabled(true);}`
## Blink_asymmetrical.cpp
* Flashes an LED with different on/off periods<br>
`toggleLED(600,100);`
## Heartbeat_gentle_fade.cpp
* Makes the LED glow and dim slowly.<br>
`heartbeat();`
## Heartbeat_pulse_fade.cpp
* Turns LED on fast then dims it slowly<br>
`heartbeatpulse();`
## Startup scheduler.cpp
* Runs various functions at various times after start-up, in this example it writes to the serial port

# Why did I write SimpleTimer?
It can be messy keeping track of millis() if you use more than one timer or delay.<br>So I wanted an easy to use self-contained non-blocking timer.<br>

SimpleTimer gives you more!<br><br>
You can run several SimpleTimers at once, and each timer can encapsulate your own private variables that you can use for whatever you want e.g to keep track of LED state, the number or state of, well, just about anything...

If all you want to do is flash an LED, this is the simplest way.
More complex tasks are also made easier, including a slow glowing/dimming heartbeat to show your software is running OK, see the example code.