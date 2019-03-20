// ---------------------------------------------
// millis_clock.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 march 20
// ---------------------------------------------
// 
// Run a clock with hours, minutes and seconds.
// The serial monitor is used for the output and
// for setting the time.
//
// The format is hh:mm:ss with 24 hours.
//

unsigned long previousMillis;
const unsigned long interval = 1000;   // 1 second

int hours, minutes, seconds;

void setup()
{
  Serial.begin( 9600);
  Serial.setTimeout( 100);    // 100ms timeout for serial input
  Serial.println( "Set the new time in hh:mm:ss format");
}

void loop()
{
  unsigned long currentMillis = millis();
  
  if( Serial.available())
  {
    delay( 100);               // wait 100ms to get whole line
    int h, a, m, b, s;
    h = Serial.parseInt();    // get integer with timeout
    a = Serial.read();        // get character, no timeout
    m = Serial.parseInt();    // get integer with timeout
    b = Serial.read();        // get character, no timeout
    s = Serial.parseInt();    // get integer with timeout

    if( a == ':' && b == ':') // check for right format
    {
      hours   = constrain( h, 0, 23);
      minutes = constrain( m, 0, 59);
      seconds = constrain( s, 0, 59);
    }
    else
    {
      Serial.println( "New time not accepted");
    }
  }

  if( currentMillis - previousMillis >= interval)
  {
    // When previousMillis would be set to currentMillis,
    // then a delay in the code would delay the clock.
    // When previousMillis is incremented with 1 second,
    // then it stays synchronized.
    previousMillis += interval;   // increment with 1 second

    seconds++;
    if( seconds >= 60)
    {
      seconds = 0;
      minutes++;
      if( minutes >= 60)
      {
        minutes = 0;
        hours++;
        if( hours >= 24)
        {
          hours = 0;
        }
      }
    }

    // Update the time to the serial monitor.
    // The format is  hh:mm:ss.
    // For example    09:30:55
    if( hours < 10)
      Serial.print( "0");
    Serial.print( hours);
    Serial.print( ":");
    if( minutes < 10)
      Serial.print( "0");
    Serial.print( minutes);
    Serial.print( ":");
    if( seconds < 10)
      Serial.print( "0");
    Serial.print( seconds);
    Serial.println();
  }
}
