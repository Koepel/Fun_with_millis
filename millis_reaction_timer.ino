// ---------------------------------------------
// millis_reaction_timer.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 march 21
// ---------------------------------------------
// 
// millis() example for a reaction timer.
//
// When the led turns on, press the button as fast as you can.
//
// A button is connected to pin 2 and GND.
//
// The LED_BUILTIN is the led on the Arduino board,
// any other digital pin can be used.
//

const int ledPin = LED_BUILTIN;
const int buttonPin = 2;

unsigned long previousMillis;
unsigned long interval;

// To calculate the average since startup,
// the total and the number of tests is stored.
unsigned long totalInterval = 0;
unsigned long numberTests = 0;


enum
{
  STATE_GET_READY,
  STATE_DELAY_FOR_LED,
  STATE_WAIT_FOR_BUTTON,
} state;


void setup()
{
  Serial.begin( 9600);
  Serial.println( "Reaction timer.");
  Serial.println( "Press the button when the led turns on.");
  
  pinMode( ledPin, OUTPUT);
  pinMode( buttonPin, INPUT_PULLUP);
  
  // Use the noise from the analog inputs,
  // to create a different random sequence each
  // time the Arduino is started.
  unsigned long noise = 0;
  for( int i = A0; i <= A5; i++)
  {
    noise += analogRead( i);
    noise <<= 4;               // for a little more random
  }
  randomSeed( noise);
}


void loop()
{
  unsigned long currentMillis = millis();

  bool buttonPressed = false;          // set default, no button pressed
  if( digitalRead( buttonPin) == LOW)  // low is active
  {
    buttonPressed = true;
  }

  switch( state)
  {
    case STATE_GET_READY:
      // Start when the button is not pressed.
      if( !buttonPressed)
      {
        Serial.println( "Get ready !");
        interval = random( 2000, 7000);  // choose a random delay for the led
        previousMillis = millis();       // remember this moment
        state = STATE_DELAY_FOR_LED;     // advance to next state
      }
      break;
    case STATE_DELAY_FOR_LED:
      if( buttonPressed)
      {
        // no cheating allowed.
        Serial.println( "The button was pressed before the led was turned on.");
        Serial.println( "Let's try again.");
        state = STATE_GET_READY;
      } 
      else if( currentMillis - previousMillis >= interval)
      {
        // Re-use the previousMillis variable.
        digitalWrite( ledPin, HIGH);     // turn led on
        previousMillis = millis();       // start timer by remembering this moment
        state = STATE_WAIT_FOR_BUTTON;
      }
      break;
    case STATE_WAIT_FOR_BUTTON:
      // Re-use the interval variable
      if( buttonPressed)
      {
        interval = currentMillis - previousMillis;
        totalInterval += interval;
        numberTests++;
        unsigned long average = totalInterval / numberTests;
        
        Serial.print( "Your reaction time is ");
        Serial.print( interval);
        Serial.print( " milliseconds, average is ");
        Serial.print( average);
        Serial.println();
        digitalWrite( ledPin, LOW);        // turn led off
        state = STATE_GET_READY;
      }
      break;
  }
  delay( 10);             // 10ms delay to avoid button bounce
}
