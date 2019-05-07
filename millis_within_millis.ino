// ---------------------------------------------
// millis_within_millis.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 january 23
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

unsigned long previousMillisOnOff;
unsigned long previousMillisBlink;

const int ledPin = LED_BUILTIN; // The digital pin to which a led is connected.

// The state for the led is the 'state_Blink'.
// That could be an integer that is HIGH or LOW, but I choose to use a bool
// with true and false. There is no reason for that, both are good.
bool state_OnOff = false;
bool state_Blink = false;


void setup()
{
  pinMode( ledPin, OUTPUT);
}


void loop()
{
  unsigned long currentMillis = millis();
  
  if( currentMillis - previousMillisOnOff >= 2000)
  {
    previousMillisOnOff = currentMillis;
    state_OnOff = !state_OnOff;
    
    if( !state_OnOff)
    {
      digitalWrite( ledPin, LOW);
    }
  }
  
  // Sometimes the part that does the blinking
  // is placed in a "update" function.
  // I prefer that as well, it keeps the loop() small and clean.
  if( state_OnOff)
  {
    if( currentMillis - previousMillisBlink >= 150)
    {
      previousMillisBlink = currentMillis;
      digitalWrite( ledPin, state_Blink ? HIGH : LOW);
      state_Blink = !state_Blink;
    }
  }
}
