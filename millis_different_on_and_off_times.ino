// ---------------------------------------------
// millis_different_on_and_off_times.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 januari 23
// ---------------------------------------------
// 
// millis() demo with different "on" and "off" times.
//
// The led of the Arduino board is used.
// It is "on" for a short time, with a few seconds in between.
//
// Created and tested at Tinkercad.com
//

unsigned long previousMillis;
unsigned long interval = 1000; // start value set to 1 second
int ledState = LOW;            // led is off at start.

void setup()
{
  pinMode( LED_BUILTIN, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  
  if( currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    
    if( ledState == HIGH) // led was on ?
    {
      interval = 3000;    // new interval is a few seconds
      ledState = LOW;     // new led state is off
    }
    else                  // led was off
    {
      interval = 400;     // new interval is a short time
      ledState = HIGH;    // new led state is on
    }
    
    digitalWrite( LED_BUILTIN, ledState); // set new led state
  }
}
