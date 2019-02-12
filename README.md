# Fun_with_millis
A few small Arduino examples using the millis() function.

The Arduino millis() function can be used in almost every situation.
These are a few small demonstration sketches to show how to use millis() in different situations.  
I hope you like them and have fun with the sketches :smile:


- **[millis_basic_demo.ino](millis_basic_demo.ino)**  
   This is the basic example. It uses the serial monitor and no extra hardware is required.
   Three different software timers with millis are used to send something to the serial monitor.
- **[millis_different_on_and_off_times.ino](millis_different_on_and_off_times.ino)**  
   An example to change the interval. No extra hardware is required. The time that a led
   is "on" is different than the time the led is "off".
- **[millis_rhythm.ino](millis_rhythm.ino)**  
   Blink a led with a rhytm. The values for the time to set the led on and off
   are read from an array.
- **[millis_single_delay.ino](millis_single_delay.ino)**  
   A single "delay" with millis(). A software timer is started. When the time is up, the
   software timer stops itself, thus creating a single event.
- **[millis_count_down.ino](millis_count_down.ino)**  
   Counting down with millis().
- **[millis_short_press_long_press.ino](millis_short_press_long_press.ino)**
   Press a button for a short time to turn a led on, and press the button for a long time 
   to turn the led off.
- **[millis_within_millis.ino](millis_within_millis.ino)**  
   Using millis() to blink a led, and another millis() software timer to turn on and off 
   the blinking.
- **[millis_measure_time.ino](millis_measure_time.ino)**  
   Use millis() and micros() to measure how long a piece of code takes. Measure for
   example how long the function analogRead() takes in three different ways.
- **[millis_and_bool.ino](millis_and_bool.ino)**  
   A boolean variable can be used to do something just once. It can also be used
   to turn something on and off by pressing the same button.
- **[millis_and_finite_state_machine.ino](millis_and_finite_state_machine.ino)**  
   This example sketch combines millis(), boolean variables and a finite state machine.

These examples are in the Public Domain, because they are only small and basic examples for using millis().

Maybe in the future I will add a few more:  
Softly pulse a led PWM and make the brightness according to the human eye.  
Play a tune without delay, using millis() and a "update" function as an alternative for the ToneMelody example.  
Increase a value with acceleration when a button is kept pressed.  
