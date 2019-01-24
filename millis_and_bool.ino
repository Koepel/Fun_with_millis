// ---------------------------------------------
// millis_and_bool.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 januari 23
// ---------------------------------------------
// 
// Example of millis() and boolean variables.
// For example to turn something on with a button, and turn it
// of by pressing the same button.
// Also showing how to use boolean variables to do something just once.
//
// The button is connected to pin 2 and GND.
// Pin 2 is therefor LOW when the button is pressed.
//
// When the button is pressed, the led turns on and the timer starts.
// There are two trigger times, at 3 seconds and at 10 seconds.
// The timer stops when the button is pressed again.


unsigned long previousMillis;
const unsigned long triggerTime1 = 3000UL;      // 3 seconds
const unsigned long triggerTime2 = 10000UL;     // 10 seconds
bool enableTrigger1 = false;
bool enableTrigger2 = false;

const int buttonPin = 2;
int last_button_state = HIGH;     // default for button not pressed.
bool enableTimer = false;

void setup()
{
  Serial.begin( 9600);
  Serial.println( "Example of millis() and a button");

  pinMode( buttonPin, INPUT_PULLUP);
  pinMode( LED_BUILTIN, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  
  int button_state = digitalRead( buttonPin);
  if( button_state != last_button_state)
  {
    if( button_state == LOW)      // button was pressed just now ?
    {
      if( !enableTimer)
      {
        previousMillis = currentMillis;  // remember this time
        enableTimer = true;              // enable the timer
        enableTrigger1 = true;
        enableTrigger2 = true;
        digitalWrite( LED_BUILTIN, HIGH);
        Serial.println( "The button is pressed. The timer runs.");
      }
      else
      {
        enableTimer = false;             // stop the timer
        digitalWrite( LED_BUILTIN, LOW);
        Serial.print( "The button is pressed. The timer has stopped after ");
        Serial.print( (currentMillis - previousMillis)/1000);
        Serial.println( " seconds");
      }
    }
    
    last_button_state = button_state;   // remember the button state to detect a change
  }
  
  if( enableTimer)           // is the timer running ?
  {
    if( enableTrigger1)
    {
      if( currentMillis - previousMillis >= triggerTime1)
      {
        enableTrigger1 = false;       // turns itself off, to run only once
        Serial.println( "Trigger at 3 seconds.");
      } 
    }
    
    if( enableTrigger2)
    {
      if( currentMillis - previousMillis >= triggerTime2)
      {
        enableTrigger2 = false;       // turns itself off, to run only once
        Serial.println( "Trigger at 10 seconds.");
      }
    }
  }
  
  delay( 10);                 // a small delay to avoid button bounce
}
