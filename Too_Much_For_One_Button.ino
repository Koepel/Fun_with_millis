// ---------------------------------------------
// Too_Much_For_One_Button.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 june 27
// ---------------------------------------------
// 
// Selecting more than 40 different commands with a single button.
// That is just too much for one button, and it is hard to use.
// The first 12 button sequences are reasonably doable with some practice.
//
// The sketch might not be very educational.
// It is not just a simple example.
//
// A button is connected to pin 2 and GND.
//
// Explanation of the list of possible sequences:
//     S     Short press, shorter than 190ms.
//     L     Long  press, between 190ms and 900ms. 
//     -     Short pause, shorter than 190ms
//     =     Long  pause, between 190ms and 900ms.
//     Z     A long continuous press, longer than 900ms.
//           This is considered to be a 'Escape'.
//           Any preceding sequence with the button is discarded.
//           The 'Escape' becomes active while the button is still
//           being pressed to be able to make a beep sound with a piezo.
//     '\0'  A pause longer than 900ms is the end of a sequence.
//


#define MAX_SEQUENCE 8

#define ID_ESCAPE    100
#define ID_ERROR     101

typedef struct idSequence_STRUCT
{
  byte id;
  char sequence[MAX_SEQUENCE];
} idSequence;

// For the Arduino Uno this list of 333 bytes could be placed in PROGMEM.
const idSequence list[] =
{
   0, "L",          // long press (between 190ms and 900ms)
   1, "S",          // short press (less than 190ms)
   2, "S-S",        // short press, short pause, short press
   3, "S-S-S",
   4, "S-S-S-S",
   5, "L-L",
   6, "S=S",
   7, "L=L",
   8, "S-L",
   9, "L-S",
  10, "S=L",
  11, "L=S",

  // The next sequences are not easy to enter, maybe it's better not to use them.
  12, "L-L-L",
  13, "S=S=S",
  14, "L=L=L",
  15, "S-S=S",
  16, "S=S-S",
  17, "L-L=L",
  18, "L=L-L",
  19, "S-S-L",
  20, "S-L-L",
  21, "S-L-S",
  22, "L-S-S",
  23, "L-L-S",
  24, "L-S-L",
  25, "S=S=L",
  26, "S=L=S",
  27, "S=L=L",
  28, "L=S=S",
  29, "L=L=S",
  30, "L=S=L",
  31, "S=L-S",
  32, "S=S-L",
  33, "S-L=S",
  34, "S-S=L",
  35, "S-L=L",
  36, "L=L-S",
  37, "L=S-L",
  38, "L-L=S",
  39, "L-S=L",
  40, "L-S=S",
  41, "S=L-L",
  42, "L=S-S",

  // These are special situations:
  ID_ESCAPE, "E",        // Escape
  ID_ERROR,  "Z",        // Error
};

char input[20];          // Only 6 are needed, but more is allowed, e.g. to detect a open input with noise.
size_t index;            // index of 'input[]'
#define indexPlusPlus    if( index < (sizeof( input) - 1)) index++

unsigned long previousMillisPressed;
unsigned long previousMillisReleased;
const unsigned long shortDelay = 190;
const unsigned long longDelay  = 900;

const byte pinButton = 2;

byte lastButtonState = HIGH;  // set default to not active
bool sequenceActive = false;  // true when a button sequence is active


void setup()
{
  Serial.begin( 9600);
  Serial.println( "Press the button in a specific sequence");
  pinMode( pinButton, INPUT_PULLUP);
}


void loop()
{
  // --------------------------------------------
  // Create temporary variables
  // --------------------------------------------

  bool processInput = false;             // set to default

  unsigned long currentMillis = millis();


  // --------------------------------------------
  // Gather all information
  // --------------------------------------------

  byte buttonState = (byte) digitalRead( pinButton);


  // --------------------------------------------
  // Check the button events
  // --------------------------------------------

  if( buttonState != lastButtonState)
  {
    if( buttonState == LOW)             // LOW when the button is pressed
    {
      // Button event: the button has been pressed just now.
      if( sequenceActive)
      {
        // Calculate for how long the button was released.
        unsigned long t = currentMillis - previousMillisReleased;
        if( t < shortDelay)
        {
          input[index] = '-';           // short pause between button presses
          indexPlusPlus;                // macro to increment index
        }
        else if( t < longDelay)
        {
          // A valid pause
          input[index] = '=';           // long pause between button presses
          indexPlusPlus;                // macro to increment index
        }
      }
      else
      {
        // The button was pressed, but a sequence is not active.
        // That means the button is pressed for the first time.
        sequenceActive = true;
      }

      // Update previousMillisPressed to remember the moment of the last time
      // the button was pressed.
      previousMillisPressed = currentMillis;
    }
    else
    {
      // Button event: the button has been released just now.
      if( sequenceActive)               // ignore releasing the button if 'Escape' was given before.
      {
        // Calculate for how long the button was pressed.
        unsigned long t = currentMillis - previousMillisPressed;

        if( t < shortDelay)
        {
          input[index] = 'S';           // button was pressed for a short time
          indexPlusPlus;                // macro to increment index
        }
        else if( t < longDelay)
        {
          // A valid pause
          input[index] = 'L';           // button was pressed for a long time
          indexPlusPlus;                // macro to increment index
        }
      }

      // Update previousMillisReleased to remember the moment of the last time
      // the button was released.
      previousMillisReleased = currentMillis;
    }

    lastButtonState = buttonState;      // remember button state to detect a change next time
  }


  // --------------------------------------------
  // Check the button state
  // --------------------------------------------

  if( sequenceActive)
  {
    if( buttonState == LOW)             // the button state is being pressed ?
    {
      // Button state: the button is pressed.
      if( currentMillis - previousMillisPressed >= longDelay)
      {
        // longer than 900ms pressed, "Escape" code.
        // Ignore any input sequence up to now.
        strcpy( input, "E");
        processInput = true;
      }
    }
    else                                // the button state is not pressed ?
    {
      // Button state: the button is not pressed.
      if( currentMillis - previousMillisReleased >= longDelay)
      {
        // No button pressed for some time.
        // End of the sequence.
        input[index] = '\0';            // finish the input sequence
        processInput = true;
      }
    }

    // If reading a input sequence is busy, but not yet completed, then do an extra safety check
    // Check if the input buffer is filled completely with noise or random button presses
    // If it is, stop reading and return an error identifier of -1.
    if( !processInput)
    {
      if( index >= sizeof( input) - 1)
      {
        // Throw away everything in the input buffer and set error sequence "Z".
        strcpy( input, "Z");
        processInput = true;
      }
    }
  }


  // --------------------------------------------
  // Process the sequence of the button input
  // --------------------------------------------
  if( processInput)
  {
    bool found = false;           // set default
    byte identifier = ID_ERROR;   // set default, no valid sequence

    // Compare the sequence to the known sequences.
    for( size_t i=0; i < (sizeof( list) / sizeof( list[0])) && !found; i++)
    {
      if( strcmp( input, list[i].sequence) == 0)
      {
        found = true;
        identifier = list[i].id;
        break;                          // found it, no need to search the rest
      }
    }

    Serial.print( "Identifier: ");
    Serial.print( identifier);

    // Sound a beep for 'Escape' or wrong input.
    if( identifier == ID_ESCAPE)  // 'Escape'
    {
      Serial.print( " \"beep\" (escape)");
    }
    else if( identifier == ID_ERROR)
    {
      Serial.print( " \"beep\" (wrong input)");
    }
    Serial.println();
    
    // Reset the variables and clear the sequence input buffer
    sequenceActive = false;
    index = 0;
    input[0] = '\0';
  }

  delay( 10);    // a delay as a simple debounce for the button
}
