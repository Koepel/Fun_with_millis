// ---------------------------------------------
// millis_led_heartbeat.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// Version 1, 2019 february 17
// Version 2, 2019 march 20
//   A few minor changes.
// ---------------------------------------------
//
// A led that blinks softly like a heartbeat.
// The millis() function is used to update the led brightness.
//
// A led with a resistor should be connected to one of the PWM capable pins.
// Instead of analogWrite(), the value could also be used for a NeoPixel.
//


const int ledPin = 3;              // This must be a PWM pin.

// Assuming that a led update of 25 Hz is fast enough, then the interval is 40 ms.
unsigned long previousMillis;
const unsigned long interval = 40; // update interval

float x = -0.5;                    // from -0.5 to 0.5


void setup()
{
}


void loop()
{
  unsigned long currentMillis = millis();

  if( currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    // The standard deviation is:
    //    y = e ^ ( -0.5 * x * x )
    // This sketch uses:
    //    y = expf ( -s * squaref ( x ) )
    //
    // The brightness to the human eye is close to a logarithmic scale with base 10.
    // Since an exponential curve is used, it is already a nice pulse.

    const float s1 = 150.0;        // steepness first pulse
    const float s2 = 400.0;        // steepness second pulse
    const float d = 0.13;          // distance between the pulses
    const float f = 0.6;           // frequency of heartbeat in Hz
    const float a = 200.0;         // amplitude of brightness

    // Set lowest value to 1, so the led does not go completely off
    float y = 1.0;

    // First pulse.
    y += a * expf( -s1 * squaref( x + d));

    // Second pulse at lower brightness.
    y += a * expf( -s2 * squaref( x - d)) * 0.30;

    // The total value of y should not be above 255.
    analogWrite( ledPin, int( y));

    x += f * float( interval) / 1000.0;  // divide interval by 1000 because it is in milliseconds
    if( x >= 0.5)
      x -= 1.0;
  }
}
