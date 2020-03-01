// ---------------------------------------------
// millis_rhythm.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 january 23
// ---------------------------------------------
// 
// millis with a rhythm.
//
// Make a led blink with a specific rhythm, using millis.
//

const int ritme_table[] =
{
   160, 200,   // 160 ms on, 200 ms off
   140, 200,
   120, 200,
   100, 200,
    80, 1000,
    80, 120,
    80, 120,
    80, 1000,
  1000, 500,
};

unsigned long previousMillis;
int index = 0;

const int ledPin = 13;


void setup()
{
  pinMode( ledPin, OUTPUT);
  
  // The table starts with the led on.
  // After 160 ms it will be turned off.
  digitalWrite( ledPin, HIGH);
  previousMillis = millis();
}


void loop()
{
  unsigned long currentMillis = millis();
  
  if( currentMillis - previousMillis >= ritme_table[index])
  {
    previousMillis = currentMillis;
    
    if( index % 2 == 0)  // check if the index is an even number
    {
      digitalWrite( ledPin, LOW);
    }
    else
    {
      digitalWrite( ledPin, HIGH);
    }
    
    index++;
    if( index >= sizeof(ritme_table) / sizeof(int))
    {
      index = 0;
    }
  }
}
