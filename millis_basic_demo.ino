// ---------------------------------------------
// millis_basic_demo.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 january 23
// ---------------------------------------------
// 
// millis_basic_demo.ino
//
// Running three different things with millis().
// The serial monitor is used to show the three different things.
//

unsigned long previousMillisDot;
const unsigned long intervalDot = 200;

unsigned long previousMillisHello;
const unsigned long intervalHello = 1600;

unsigned long previousMillisRandom;
unsigned long intervalRandom = 1000;

void setup()
{
  Serial.begin( 9600);
  Serial.println();
  Serial.println( "The sketch has started");
}

void loop()
{
  unsigned long currentMillis = millis();
  
  if( currentMillis - previousMillisDot >= intervalDot)
  {
    previousMillisDot = currentMillis;
    
    Serial.print( ".");
  }
  
  if( currentMillis - previousMillisHello >= intervalHello)
  {
    previousMillisHello = currentMillis;
    
    Serial.println();
    Serial.print( "Hello");
  }
  
  if( currentMillis - previousMillisRandom >= intervalRandom)
  {
    previousMillisRandom = currentMillis;
    
    intervalRandom = (unsigned long) random( 500, 5000);
    
    Serial.print( "Random");
  }
}
