// ---------------------------------------------
// millis_short_press_long_press.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 february 12
// ---------------------------------------------
// 
// Short press and long press a button.
//
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

const int buttonPin = 2;
const int ledPin = LED_BUILTIN;

unsigned long previousMillis;
const unsigned long interval = 2000;   // 2 seconds
bool ledOn = false;                    // default, led is off
int lastButtonState = HIGH;            // HIGH is idle (button not pressed)

void setup()
{
  pinMode( buttonPin, INPUT_PULLUP);
  pinMode( ledPin, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();

  int buttonState = digitalRead( buttonPin);

  if( buttonState != lastButtonState)  // something changed ?
  {
    if( buttonState == LOW)            // button is pressed ?
    {
      previousMillis = currentMillis;  // remember millis value
    }
    else                               // button is released
    {
      if( currentMillis - previousMillis < interval) // short press ?
      {
        digitalWrite( ledPin, HIGH);   // turn led on
        ledOn = true;                  // remember that led is on
      }
    }

    lastButtonState = buttonState;     // remember new button state
  }
  else if( buttonState == LOW && ledOn) // button still pressed and led is on ?
  {
    if( currentMillis - previousMillis >= interval) // pressed long enough ?
    {
      digitalWrite( ledPin, LOW);
      ledOn = false;
    }
  }

  delay( 10); // a delay as a simple way to debounce the button
}
