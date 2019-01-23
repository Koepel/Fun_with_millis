// millis and a finite state machine
//
// The "State Change Detection" example is used.
// The "Blink without Delay" example is used.
// Variables of the "bool" type are used to pass on information.
// Two "previousMillis" variables are used, but a single "previousMillis" 
// could be used, because they do not overlap.
//
// The finite state machine has a few ..._INIT states.
// They are used to make a setup for the new state.
//
// A push button is connected between pin 2 and GND.


// An 'enum' is the best way to for a list of the states.
enum
{
  STATE_IDLE_INIT,
  STATE_IDLE,
  STATE_ON_INIT,
  STATE_ON_BEFORE_BUTTON,
  STATE_ON_BUTTON_2_SECONDS,
  STATE_OFF_INIT,
  STATE_OFF,
  STATE_BLINK_INIT,
  STATE_BLINK,
} state;

const int buttonPin = 2;
int last_button_value = HIGH;   // pin 2 is HIGH when button is not pressed
unsigned long previousMillisButton;

const int ledPin = 13;
int led_value;

unsigned long previousMillisBlinking;
bool blinking;   // boolean variable, should the led blink or not.


void setup()
{
  Serial.begin( 9600);
  Serial.println( "The sketch has started.");
  pinMode( buttonPin, INPUT_PULLUP);
  pinMode( ledPin, OUTPUT);
}


void loop()
{
  unsigned long currentMillis = millis();
  
  
  // ---------------------------------------------------
  // BUTTON
  // ---------------------------------------------------
  // Detect if the button changes, and pass
  // that information on, to the finite state machine.
  // Only the event of the change is passed on, because
  // this sketch did not need to know the state
  // of the button, only a change.
  // ---------------------------------------------------
  bool buttonPressed = false;
  bool buttonReleased = false;

  int button_value = digitalRead( buttonPin);

  if( button_value != last_button_value)
  {
    if( button_value == LOW)  // low is button pressed
    {
      buttonPressed = true;
    }
    else
    {
      buttonReleased = true;
    }
    last_button_value = button_value;
  }
  

  // ---------------------------------------------------
  // FINITE STATE MACHINE
  // ---------------------------------------------------
  // The final state machine uses information to
  // make decisions.
  // ---------------------------------------------------
  
  switch( state)
  {
    case STATE_IDLE_INIT:
      Serial.println( "Press the button to turn the led on.");
      state = STATE_IDLE;
      break;
    case STATE_IDLE:
      if( buttonPressed)
      {
        state = STATE_ON_INIT;
      }
      break;
    case STATE_ON_INIT:
      digitalWrite( ledPin, HIGH);
      Serial.println( "Press button longer than two seconds to turn it off.");
      state = STATE_ON_BEFORE_BUTTON;
      break;
    case STATE_ON_BEFORE_BUTTON:
      if( buttonPressed)
      {
        previousMillisButton = currentMillis;
        state = STATE_ON_BUTTON_2_SECONDS;
      }
      break;
    case STATE_ON_BUTTON_2_SECONDS:
      if( buttonReleased)
      {
        state = STATE_ON_BEFORE_BUTTON;
      }
      else
      {
        if( currentMillis - previousMillisButton >= 2000)
        {
          state = STATE_OFF_INIT;
        }
      }
      break;
    case STATE_OFF_INIT:
      digitalWrite( ledPin, LOW);
      Serial.println( "Press button to blink the led.");
      state = STATE_OFF;
      break;
    case STATE_OFF:
      if( buttonPressed)
      {
        state = STATE_BLINK_INIT;
      }
      break;
    case STATE_BLINK_INIT:
      previousMillisBlinking = currentMillis;
      blinking = true;
      Serial.println( "Press button to stop blinking.");
      state = STATE_BLINK;
      break;
    case STATE_BLINK:
      if( buttonPressed)
      {
        blinking = false;
        digitalWrite( ledPin, LOW);  // be sure to turn led off
        state = STATE_IDLE_INIT;
      }
      break;
  }
  
  
  // ---------------------------------------------------
  // BLINK WITHOUT DELAY
  // ---------------------------------------------------
  // Blinking the led is outside the final state machine.
  // The final state machine can turn the blinking on and off.
  // ---------------------------------------------------

  if( blinking)
  {
    if( currentMillis - previousMillisBlinking >= 300)
    {
      previousMillisBlinking = currentMillis;
      
      if( led_value == LOW)
      {
        led_value = HIGH;
      }
      else
      {
        led_value = LOW;
      }
      digitalWrite( ledPin, led_value);
    }
  }
  
  delay( 10);  // a delay as a simple way to debounce the button
}
