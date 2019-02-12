// ---------------------------------------------
// millis_short_press_long_press_extra.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 february 12
// ---------------------------------------------
// 
// Short press and long press a button
// Turn the led on with a short press of the button,
// the led turns on after the button is released.
// Turn the led off with a long press,
// the led turns off while the button is being pressed.
//
// The "State Change Detection" example is used.
// The "Blink without Delay" example is used.
//
// A button is connected to pin 2 and GND.
//
// The LED_BUILTIN led is the led on the Arduino board,
// any other digital pin can be used.
//
// This sketch does the same as millis_short_press_long_press.ino
// But this sketch uses a finite state machine.


enum
{
  STATE_IDLE,
  STATE_BEFORE_INTERVAL,
  STATE_AFTER_INTERVAL,
} state;

const int buttonPin = 2;
const int ledPin = LED_BUILTIN;

unsigned long previousMillis;
const unsigned long interval = 2000;   // 2 seconds

void setup()
{
  pinMode( buttonPin, INPUT_PULLUP);
  pinMode( ledPin, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  int buttonState = digitalRead( buttonPin);

  switch( state)
  {
    case STATE_IDLE:
      // The state is idle.
      // Waiting for the button to be pressed.
      // The led might be on or off.
      if( buttonState == LOW)           // button pressed ?
      {
        state = STATE_BEFORE_INTERVAL;  // advance to next state
        previousMillis = currentMillis; // remember millis
      }
      break;
    case STATE_BEFORE_INTERVAL:
      if( buttonState == HIGH)          // button released after short time ?
      {
        digitalWrite( ledPin, HIGH);    // turn led on
        state = STATE_IDLE;             // returnt idle to wait for button
      }
      else if( currentMillis - previousMillis >= interval) // button pressed long enough ?
      {
        digitalWrite( ledPin, LOW);     // turn led off
        state = STATE_AFTER_INTERVAL;   // advance to next state
      }
      break;
    case STATE_AFTER_INTERVAL:
      // Wait until button is released to return to idle
      if( buttonState == HIGH)          // HIGH is not pressed
      {
        state = STATE_IDLE;
      }
      break;
  }

  delay( 10); // a delay as a simple way to debounce the button
}
