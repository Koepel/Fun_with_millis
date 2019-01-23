// millis() demo for a count down timer.
//
// A button is connected to pin 2 and GND.
// The count down starts as soon as the button
// is pressed.
//

const int buttonPin = 2;

const long startCount = 5000; // start countdown with 5 seconds
unsigned long previousMillisCounter;
bool counting = false;

// An extra timer with millis is used to show the count down time.
// For a LCD display, the interval can be 200 ms.
// For the serial monitor, the interval can also be 200 ms.
// For a 7-segment display, the update can be done
// at full speed without the use of millis().
unsigned long previousMillisUpdate;
const unsigned long intervalUpdate = 200;

void setup() 
{
  pinMode( buttonPin, INPUT_PULLUP);

  Serial.begin( 9600);
  Serial.println( "Press the button");
}

void loop() 
{
  unsigned long currentMillis = millis();
  
  if( !counting)
  {
    // As soon as the button is pressed, the counter is
    // made active and the value of millis() is remembered.
    
    if( digitalRead( buttonPin) == LOW)
    {
      previousMillisCounter = currentMillis;
      counting = true;
    }
  }
  else
  {
    // To prevent a rollover problem, the time that has passed
    // since the start is calculated with unsigned long.
    // After that the down-counter value is calculated with long,
    // because it might have passed the end time and became negative.
    
    unsigned long countUpValue = currentMillis - previousMillisCounter;  // must be unsigned long !
    long countDownValue = startCount - long( countUpValue);  // must be long !
    
    // Check if the end time is reached
    if( countDownValue <= 0)
    {
      countDownValue = 0;

      // Also print the value of 0 to the output
      Serial.println( countDownValue);
      
      Serial.println( "Press the button");
      counting = false;
    }
    else
    {
      // Update the output.
      if( currentMillis - previousMillisUpdate >= intervalUpdate)
      {
        previousMillisUpdate = currentMillis;

        Serial.println( countDownValue);
      }
    }
  }
}
