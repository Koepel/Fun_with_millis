// ---------------------------------------------
// millis_single_delay.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 januari 23
// ---------------------------------------------
// 
// One shot software timer with millis().
// Turn on a led for 4 seconds when a switch is used.
// 
// The 4 seconds starts when the switch is released.
// When the timing should start at the moment the
// switch is pressed, then the State Change Detection
// should be added.
//
// The switch is connected to pin 2 and GND.
//
// The LED_BUILTIN led is the led on the Arduino board,
// any other digital pin can be used.
//

const int switchPin = 2;
const int ledPin = LED_BUILTIN;

unsigned long previousMillis;
const unsigned long interval = 4000;
bool enabled = false;

void setup()
{
  pinMode( switchPin, INPUT_PULLUP);
  pinMode( ledPin, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  
  if( digitalRead( switchPin) == LOW)  // low is active
  {
    digitalWrite( ledPin, HIGH);  // turn on led
    previousMillis = currentMillis;
    enabled = true;        // turn on software timer
  }
  
  
  if( enabled)      // software timer is active ?
  {
    if( currentMillis - previousMillis >= interval)
    {
      digitalWrite( ledPin, LOW);  // turn off led
      enabled = false;     // stop software timer
    }
  }
}
