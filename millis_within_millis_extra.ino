// ---------------------------------------------
// millis_within_millis_extra.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// 2019 may 7        First version, by Koepel.
// ---------------------------------------------
// 
// millis within millis with specific working.
//
// This is the same as millis_within_millis.ino, but with these extras:
//   - The time that the led is on is not the same as the time that the led is off.
//   - The time that the blinking is on is not the same as the time that the blinking is off.
//   - When the blinking is started, the led turns on immediate.
//   - When the blinking is stopped and the led is on, then the led stays on
//     until it has finished its time to stay on.
//     
// To make the led finish its "on" time before turning off, the command to
// turn it off is buffered with an extra variable 'enableBlinkBuffered'.
//
// This examples was to show the extra variable to buffer the command to turn the led off.
// However, it turns out to be hard to understand. I have not even tested it very well.
//
// The LED_BUILTIN is the led on the Arduino board,
// any other digital pin can be used.


const int ledPin = LED_BUILTIN;       // The digital pin to which a led is connected.

unsigned long previousMillisEnableBlink;
unsigned long intervalEnableBlink;
const unsigned long enableBlinkOnTime = 6000;   // 6 seconds blinking
const unsigned long enableBlinkOffTime = 3000;  // 3 seconds no blinking

unsigned long previousMillisBlink;
unsigned long intervalBlink;
const unsigned long blinkOnTime = 450;          // 450 ms led is on
const unsigned long blinkOffTime = 700;         // 700 ms led is off

bool enableBlink;                     // true for blinking, false for off.
bool enableBlinkBuffered;             // buffered variable to turn off the blinking nicely
bool blink = false;                   // true (led on) or false (led off)


void setup()
{
  pinMode( ledPin, OUTPUT);

  intervalEnableBlink = enableBlinkOffTime;     // start with blinking off, set the interval
}


void loop()
{
  unsigned long currentMillis = millis();

  if( currentMillis - previousMillisEnableBlink >= intervalEnableBlink)
  {
    previousMillisEnableBlink = currentMillis;
    enableBlink = !enableBlink;       // true becomes false, and false becomes true
    
    if( enableBlink)
    {
      intervalEnableBlink = enableBlinkOnTime;
      
      // The blinking should start
      // It can be started here, but with different code it can be started in the blinking code.
      digitalWrite( ledPin, HIGH);
      previousMillisBlink = currentMillis;
      intervalBlink = blinkOnTime;
      blink = true;
      enableBlinkBuffered = true;     // start it now
    }
    else
    {
      intervalEnableBlink = enableBlinkOffTime;
    }
  }

  if( enableBlinkBuffered)                // is the blinking enabled ?
  {
    if( currentMillis - previousMillisBlink >= intervalBlink)
    {
      previousMillisBlink = currentMillis;
      blink = !blink;                     // true becomes false, and false becomes true

      // The next line is the buffering of the 'enableBlink'.
      // This is executed at the moment the led is turned on or off.
      enableBlinkBuffered = enableBlink;  // turn off now if it is false

      if( blink && enableBlink)           // do not start a new "on" when it should turn off.
      {
        intervalBlink = blinkOnTime;
        digitalWrite( ledPin, HIGH);
      }
      else
      {
        intervalBlink = blinkOffTime;
        digitalWrite( ledPin, LOW);
      }
    }
  }
}
