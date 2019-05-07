// ---------------------------------------------
// millis_within_millis.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// 2019 january 23   First version, by Koepel.
// 2019 may 7        Changed name of variables, by Koepel
// ---------------------------------------------
//
// millis within millis
//
// Blink a led for some time, and keep it off for some time.
//
// Because millis is timing based, it deals with events.
// Therefor the second millis timer is not inside the first
// one, but a bool variable is used to pass on information.
//
// Since the blinking can be turned off at any moment,
// the led is turned off when the blinking stops.
//
// The LED_BUILTIN is the led on the Arduino board,
// any other digital pin can be used.

unsigned long previousMillisEnableBlink; // for turning on and off the blinking
unsigned long previousMillisBlink;    // for the blinking of the led

const int ledPin = LED_BUILTIN;       // The digital pin to which a led is connected.

// The state for the led is the variable 'blink'.
// That could be an integer that is HIGH or LOW, but I choose to use a bool
// with true and false. There is no reason for that, both are good.
bool enableBlink = false;
bool blink = false;                   // true (led on) or false (led off)


void setup()
{
  pinMode( ledPin, OUTPUT);
}


void loop()
{
  unsigned long currentMillis = millis();

  if( currentMillis - previousMillisEnableBlink >= 2000)
  {
    previousMillisEnableBlink = currentMillis;
    enableBlink = !enableBlink;       // true becomes false, and false becomes true
    
    if( !enableBlink)
    {
      digitalWrite( ledPin, LOW);     // when blinking stops, be sure the led is off
    }
  }

  // Sometimes the part that does the blinking is placed in a "update" function.
  if( enableBlink)                    // is the blinking enabled ?
  {
    if( currentMillis - previousMillisBlink >= 150)
    {
      previousMillisBlink = currentMillis;
      digitalWrite( ledPin, blink ? HIGH : LOW);  // turn bool variable into HIGH and LOW
      blink = !blink;                 // true becomes false, and false becomes true
    }
  }
}
