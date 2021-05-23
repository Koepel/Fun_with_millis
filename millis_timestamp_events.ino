// ---------------------------------------------
// millis_timestamp_events.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 april 13, Version 1
// 2021 may 23, Version 2
//   Added a small delay of 2ms at the end of the loop(),
//   because button-bounching could fill the queue
//   with a single press on the button.
// ---------------------------------------------
// 
// Record events (button presses and button releases)
// and give each event a timestamp with millis.
// Put the data in a queue and use that to delay
// the events before they are send to the output (a led).
//
// A button is connected to pin 2 and GND.
//
// The LED_BUILTIN is the led on the Arduino board,
// any other digital pin can be used.
//

#define NUM_SAMPLES 100

struct EventQueueStruct
{
  unsigned long timeStamp;   // the timestamp (from millis)
  int event;                 // the event (HIGH or LOW for led)
};

EventQueueStruct myEvents[NUM_SAMPLES];

int indexIn = 0;             // index where to put new data
int indexOut = 0;            // index where to read data

const unsigned long interval = 2000UL;  // delay

const int pinButton = 2;     // button to this pin and GND
const int pinLed = LED_BUILTIN; // The digital pin to which a led is connected.

int last_button_state;


void setup()
{
  pinMode( pinButton, INPUT_PULLUP);
  pinMode( pinLed, OUTPUT);

  last_button_state = digitalRead( pinButton);
}


void loop()
{
  unsigned long currentMillis = millis();

  // --------------------------------------
  // Write any button event to the queue.
  // --------------------------------------

  int buttonState = digitalRead( pinButton);
  if( buttonState != last_button_state) // button changed ?
  {
    // Calculate the new index.
    // The queue could be full.
    // The data is only stored and the index is only advanced,
    // when everything is okay.
    
    int newIndex = indexIn + 1;
    if( newIndex >= NUM_SAMPLES)
    {
      newIndex = 0;
    }

    if( newIndex != indexOut)      // The queue is not full ?
    {
      // A LOW from the button is a HIGH for the led.
      int ledstate = (buttonState == LOW) ? HIGH : LOW;

      myEvents[indexIn].timeStamp = currentMillis;
      myEvents[indexIn].event = ledstate;

      indexIn = newIndex;          // set index for next data
    }

    last_button_state = buttonState;  // remember button state to detect a change
  }

  // --------------------------------------
  // Read the queue and process the events.
  // --------------------------------------

  // The queue is empty when the indexIn is the same
  // as the indexOut.
  if( indexOut != indexIn)            // something in the queue ?
  {
    if( currentMillis - myEvents[indexOut].timeStamp >= interval)
    {
      digitalWrite( pinLed, myEvents[indexOut].event);

      indexOut++;
      if( indexOut >= NUM_SAMPLES)
      {
        indexOut = 0;
      }
    }
  }
  
  delay( 2);    // slow down the sketch to reduce button bounching
}
