// Use millis() and micros() to measure how long a piece of code takes.
//
// The Serial.flush() is used to wait until the data is transmitted,
// so there will be no more interrupts from the serial bus.
// To be sure the Serial.flush() is also followed by a delay.


// The macro X1000 executes something 1000 times.
#define X10(a)      a;a;a;a;a;a;a;a;a;a
#define X1000(a)    X10(X10(X10(a)))


void setup()
{
  Serial.begin( 9600);
  Serial.println( "Using millis() to measure how long a piece of code takes.");
  Serial.println( "Column 1: Calculated pi.");
  Serial.println( "Column 2: The time the calculation of pi took in milliseconds.");
  Serial.println( "Column 3: A single analogRead with micros() with interrupts disabled.");
  Serial.println( "Column 4: A single analogRead with micros() and interrupts on.");
  Serial.println( "Column 5: Thousand analogRead with millis.");
  Serial.flush();
  delay( 100);
}


void loop()
{
  unsigned long t1, t2, result;

  // -------------------------------------------------

  // Basic measurement.
  // Measure how long the function "calcPi" takes in milliseconds.

  t1 = millis();           // get millis
  float f = calcPi();      // call the function under test
  t2 = millis();           // get millis() again
  result = t2 - t1;        // calcuate the difference

  Serial.print( f, 6);     // print the calculated value of pi as well
  Serial.print( ",  ");
  Serial.print( result);
  Serial.print( ",  ");
  Serial.flush();
  delay( 100);

  // -------------------------------------------------
  
  // Using micros() to calculate how long the function analogRead() takes.
  // The interrupts are turned off for better accuracy.
  // This will work on a Arduino Uno, but might not work on all boards.
  // For an Arduino Uno, the micros() is not accurate to the microsecond.
  
  noInterrupts();
  t1 = micros();
  analogRead(A0);
  t2 = micros();
  interrupts();
  result = t2 - t1;

  Serial.print( result);
  Serial.print( ",  ");
  Serial.flush();
  delay( 100);

  // -------------------------------------------------

  // Using micros() with interrupts enabled
  
  t1 = micros();
  analogRead(A0);
  t2 = micros();
  result = t2 - t1;

  Serial.print( result);
  Serial.print( ",  ");
  Serial.flush();
  delay( 100);

  // -------------------------------------------------

  // Using millis() with interrupts enabled.
  // The millis() will not work without interrupts enabled.
  // The function that is tested is executed 1000 times.
  // The resulting time could be divided by 1000, or the result could be seen as microseconds.
  // Because the function under test is executed 1000 times, the glitches by interrupts
  // are averaged, and overhead has less influence, this gives a more steady result.

  t1 = millis();
  X1000(analogRead(A0));       // The X1000 macro expands it thousand times
  t2 = millis();
  result = t2 - t1;

  Serial.print( result);
  Serial.print( ",  ");
  Serial.flush();
  delay( 100);

  // -------------------------------------------------
  
  Serial.println();
  Serial.flush();
  delay( 100);
}


float calcPi()
{
  float x = 4.0;
  float pi = 4.0;

  for( unsigned long t = 3UL; t < 100000UL; t += 2UL)
  {
    x = -x;
    pi += x / float( t);
  }

  return( pi);
}
