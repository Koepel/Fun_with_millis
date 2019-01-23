# Fun_with_millis
A few small Arduino examples using the millis() function.

The Arduino millis() function can be used in almost every situation.
These are a few small demonstration sketches to show how to use millis() in different situations.


 - millis_basic_demo.ino  
   This is the basic example. It uses the serial monitor and no extra hardware is required.
   Three different software timers with millis are used to send something to the serial monitor.
 - millis_different_on_and_off_times.ino  
   An example to change the interval. No extra hardware is required. The time that a led
   is "on" is different than the time the led is "off".
 - millis_single_delay.ino  
   A single "delay" with millis(). A software timer is started. When the time is up, the
   software timer stops itself, thus creating a single event.
