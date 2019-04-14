// ---------------------------------------------
// millis_serial_timeout.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 april 3
// ---------------------------------------------
//
// Read data from the serial port without waiting.
//
// Sometimes a command from the serial monitor has a carriage return,
// or a linefeed, or both or neither.
// To allow all those situations, a timeout with millis() is used
// to use that as well as the end of the serial data.
//

const int ledPin = LED_BUILTIN;      // The digital pin to which a led is connected.

unsigned long previousMillis;
const unsigned long timeout = 100;   // timeout in milliseconds

char buffer[20];
int index;

void setup()
{
  Serial.begin( 9600);
  Serial.println( "Enter a command");
  Serial.println( "Try \"led on\" or \"led off\"");

  pinMode( ledPin, OUTPUT);

  // clear the buffer
  index = 0;
  buffer[0] = '\0';
}

void loop()
{
  bool processCommand = false;

  if( Serial.available() > 0)          // new data received ?
  {
    int inChar = Serial.read();
    previousMillis = millis();         // remember moment of last received data
    
    if( inChar == '\n' || inChar == '\r')  // end of line ?
    {
      processCommand = true;
    }
    else
    {
      buffer[index] = (char) inChar;  // put new data in the buffer
      if( index < (int)(sizeof( buffer) - 1))  // the 'sizeof' returns an unsigned size_t
      {
        index++;
      }
      else
      {
        // The buffer is full, too much data was received.
        // Process the command and (for safety) clear
        // the remaining of the data.
        // With a low baudrate, it is possible that still
        // extra characters will come in after this.
        processCommand = true;
        
        while( Serial.available() > 0)
        {
          Serial.read();
        }
      }
      buffer[index] = '\0';          // set a new zero-terminator
    }
  }

  // The timeout should only be active when data is being received.
  // That is checked with the 'index' variable, as soon as
  // it is higher than zero, then data is being received.
  if( index > 0)
  {
    if( millis() - previousMillis >= timeout)
    {
      processCommand = true;
    }
  }

  if( processCommand)
  {
    // The data that is received and stored in the buffer
    // will be processed.
    // It is possible that the buffer is still empty,
    // for example when only a carriage return or linefeed
    // was received.

    Serial.print( "Command received: ");
    Serial.println( buffer);

    if( strcmp( buffer, "led on") == 0)
    {
      digitalWrite( ledPin, HIGH);
    }
    else if( strcmp( buffer, "led off") == 0)
    {
      digitalWrite( ledPin, LOW);
    }

    // clear the buffer
    index = 0;
    buffer[0] = '\0';
  }
}
