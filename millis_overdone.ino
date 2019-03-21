// ---------------------------------------------
// millis_overdone.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 march 21
// ---------------------------------------------
// 
// Using millis() is fun, but to overdo it can be even more fun.
//
// This sketch runs 400 millis timers at the same time on a Arduino Uno,
// and 7000 millis timers on a Arduino Zero or MKR board.
// All millis timers are used to toggle the system led.
//
// When only short times are used, it is allowed to use the
// lowest 16 bits of the millis() value.
// It will cause a rollover more often, so extra care should be taken
// to avoid the rollover problem.
//
// Arduino Uno:
// ------------
// An Arduino Uno runs at 16MHz and has 2kbyte of RAM. 
// When using the 16 lowest bits of millis, 
// then 400 different software timers can run at the same time.
// The accuracy is within the millisecond.
//
// Arduino Zero or MKR:
// --------------------
// Running at 48MHz with 32kbyte of RAM.
// When using the 16 lowest bits of millis, 
// then 7000 different software timers can run at the same time.
// The accuracy is about 4 milliseconds, because testing 7000 timers takes
// some time.
//


#if defined __AVR__
#define NUMBER_TIMERS 400               // 400 millis timers for 16MHz AVR microcontrollers.
#define SERIAL_PORT Serial             // Use Serial for Arduino Uno or SerialUSB for Leonardo.
#else
#define NUMBER_TIMERS 7000              // 7000 millis timers for other boards.
#define SERIAL_PORT SerialUSB          // Use Serial1 or SerialUSB (native) for Arduino Zero and MKR.
#endif


uint16_t previousMillisOverdone[NUMBER_TIMERS];
uint16_t intervalOverdone[NUMBER_TIMERS];

// An extra millis timer is used to send the seconds to the the serial monitor.
unsigned long previousMillis;
const unsigned long interval = 1000;
unsigned long count;

const int ledPin = LED_BUILTIN;         // The digital pin to which a led is connected.

void setup()
{
  SERIAL_PORT.begin( 9600);
  while( !SERIAL_PORT);                 // Wait for serial monitor to open (Leonardo and native serial port)
  SERIAL_PORT.println( "millis_overdone");
  SERIAL_PORT.print( "Running ");
  SERIAL_PORT.print( NUMBER_TIMERS);
  SERIAL_PORT.println( " millis timers at the same time.");
  SERIAL_PORT.println( "To check if the Arduino can keep up,");
  SERIAL_PORT.println( "the number of seconds is shown in the serial monitor.");
  
  pinMode( ledPin, OUTPUT);

  // Fill the values of the interval with random values between 5 ms and 30 seconds.
  // The interval can not be near 64 seconds, because only the lowest 16 bits of millis are used.
  for( int i=0; i < NUMBER_TIMERS; i++)
  {
    intervalOverdone[i] = random( 5, 30000);
  }
}

void loop()
{
  unsigned long currentMillis = millis();

  for( int i=0; i < NUMBER_TIMERS; i++)
  {
    // The subtraction is done with two 16-bit integers.
    // The result of that is cast once more to uint16_t, 
    // because the Arduino Zero defaults to 32 bit.
    if( (uint16_t) ( (uint16_t) currentMillis - previousMillisOverdone[i]) >= intervalOverdone[i])
    {
      previousMillisOverdone[i] = (uint16_t) currentMillis;

      // Toggle the led random on or off.
      if( random( 0, 2) == 0)
      {
        digitalWrite( ledPin, LOW);
      }
      else
      {
        digitalWrite( ledPin, HIGH);
      }
    }
  }

  // An extra timer with millis, to be able to check if the Arduino can keep up.
  // The number of seconds is send to the serial monitor.
  if( currentMillis - previousMillis >= interval)
  {
    previousMillis += interval;      // add the interval to synchronize with the time.

    SERIAL_PORT.println( count++);
  }
}
