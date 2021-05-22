# Fun_with_millis

The Arduino millis() function can be used in almost every situation.
These are small demonstration sketches to show how to use millis() in different situations.  
I hope you like them and have fun with the sketches :smile:


- **[millis_basic_demo.ino](millis_basic_demo.ino)**  
   This is the basic example. It uses the serial monitor and no extra hardware is required.
   Three different software timers with millis are used to send something to the serial monitor.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299332603637400077).
- **[millis_different_on_and_off_times.ino](millis_different_on_and_off_times.ino)**  
   An example to change the interval. No extra hardware is required. The time that a led
   is "on" is different than the time the led is "off".
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299332867294495240).
- **[millis_rhythm.ino](millis_rhythm.ino)**  
   Blink a led with a rhytm. The values for the time to set the led on and off
   are read from an array.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299333036840845837).
- **[millis_single_delay.ino](millis_single_delay.ino)**  
   A single "delay" with millis(). A better name is "a single shot timer".
   A software timer is started. When the time is up, the
   software timer stops itself, thus creating a single event.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299333522927125002).
- **[millis_clock.ino](millis_clock.ino)**  
   A clock with hours, minutes and seconds. The serial monitor is used as output to show the time.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299333839432450568).
- **[millis_count_down.ino](millis_count_down.ino)**  
   Counting down with millis().
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299333967232893450).
- **[millis_short_press_long_press.ino](millis_short_press_long_press.ino)**  
   Press a button for a short time to turn a led on, and press the button for a long time 
   to turn the led off.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299334344738079241).
- **[millis_short_press_long_press_extra.ino](millis_short_press_long_press_extra.ino)**  
   This sketch does exactly the same as "millis_short_press_long_press.ino" but a finite state machine
   is used. The compiled code uses less memory, but the source code is harder to understand.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299334624465650186).
- **[millis_within_millis.ino](millis_within_millis.ino)**  
   Using millis() to blink a led, and another millis() software timer to turn on and off 
   the blinking.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299334740949860873).
- **[millis_within_millis_extra.ino](millis_within_millis_extra.ino)**  
   The same as "millis_within_millis.ino", but with extra specific working.
   The led does not turn off immediately, but it turns off at the end of its "on" time.
   That is done by using a extra (buffered) boolean variable.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299334903709827592).
- **[millis_measure_time.ino](millis_measure_time.ino)**  
   Use millis() and micros() to measure how long a piece of code takes. Measure for
   example how long the function analogRead() takes in three different ways.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299335057012687368).
- **[millis_soft_pulsating_led.ino](millis_soft_pulsating_led.ino)**  
   A led with soft pulsating brightness. The brightness is updated with millis() with a fixed interval.  
   A led and a resistor is needed, and a PWM pin is used.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299335245194330637).
- **[millis_led_heartbeat.ino](millis_led_heartbeat.ino)**  
   A led that blinks softly like a heartbeat, using millis() to update the brightness.  
   A led and a resistor is needed, and a PWM pin is used.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299335475373539848).
- **[micros_software_PWM.ino](micros_software_PWM.ino)**  
   Instead of millis(), the micros() function is used to create a software PWM signal.
   The brightness of a led (on any pin) can be set by entering a value in the serial monitor.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299335627234607625).
- **[millis_and_bool.ino](millis_and_bool.ino)**  
   A boolean variable can be used to do something just once. It can also be used
   to turn something on and off by pressing the same button.
- **[millis_and_finite_state_machine.ino](millis_and_finite_state_machine.ino)**  
   This example sketch combines millis(), boolean variables and a finite state machine.
- **[millis_serial_timeout.ino](millis_serial_timeout.ino)**  
   Use millis as a timeout when receiving serial data to make it possible that data is received with 
   or without a carriage return or linefeed.
- **[millis_reaction_timer.ino](millis_reaction_timer.ino)**  
   Measure how fast your reaction time is. Using millis and a finite state machine.
- **[millis_timestamp_events.ino](millis_timestamp_events.ino)**  
   Copy events from a button to a led with a delay of two seconds. 
   This example shows how to timestamp events with millis().
- **[millis_overdone.ino](millis_overdone.ino)**  
   This sketch runs 400 millis timers at the same time on a Arduino Uno, or 7000 millis timers 
   on a Arduino Zero or MKR board, or 27000 on a ESP32 board.
   [_Try this sketch with Wokwi_](https://wokwi.com/arduino/projects/299335909706301961).
- **[Too_Much_For_One_Button.ino](Too_Much_For_One_Button.ino)**  
   Use a single button to select more than 40 different commands.

These examples are in the Public Domain, because they are only small and basic examples for using millis().

Maybe in the future I will add a few more:  
Play a tune without delay, using millis() and a "update" function as an alternative for the ToneMelody example. That might already exist: https://github.com/nathanRamaNoodles/Noodle-Synth , https://github.com/end2endzone/NonBlockingRTTTL and https://github.com/ArduinoGetStarted/buzzer .  
Increase a value with acceleration when a button is kept pressed.  
Run millis timers with priority, run some always and others when there is still time.  
