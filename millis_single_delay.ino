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
// The led is the led on the Arduino board,
// any other digital pin can be used.
//
// Created and tested at Tinkercad.com

const int switchPin = 2;

unsigned long previousMillis;
const unsigned long interval = 4000;
bool enabled = false;

void setup()
{
  pinMode( switchPin, INPUT_PULLUP);
  pinMode( LED_BUILTIN, OUTPUT);
}

void loop()
{
  if( digitalRead( switchPin) == LOW)  // low is active
  {
    digitalWrite( LED_BUILTIN, HIGH);  // turn on led
    previousMillis = millis();
    enabled = true;        // turn on software timer
  }
  
  
  if( enabled)      // software timer is active ?
  {
    if( millis() - previousMillis >= interval)
    {
      digitalWrite( LED_BUILTIN, LOW);  // turn off led
      enabled = false;     // stop software timer
    }
  }      
}
