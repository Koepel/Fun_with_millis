// ---------------------------------------------
// millis_soft_pulsating_led.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// Version 1, 2019 february 17
// Version 2, 2019 march 20
//   The logarithmic scale was inverted.
//   Now using pow(10,x) instead of log10(x)
// ---------------------------------------------
//
// A led with soft pulsating brightness.
// The millis() function is used to update the led brightness.
//
// A led with a resistor should be connected to one of the PWM capable pins.
// Instead of analogWrite(), the value could also be used for a NeoPixel.
//


const int ledPin = 3;              // This must be a PWM pin.

// Assuming that a led update of 25 Hz is fast enough, then the interval is 40 ms.
unsigned long previousMillis;
const unsigned long interval = 40; // update interval

float rad = 1.5 * M_PI;            // Start the radians at 1.5 pi, to start with lowest brightness.
const float rad_increment = 0.08;  // Radians increment, for the speed of the sine wave.

void setup()
{
}

void loop()
{
  unsigned long currentMillis = millis();

  if( currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    // The brightness to the human eye is close to a logarithmic scale with base 10.
    // A sine wave is used for the wave of the pulse.
    // The sine wave is going through a exponential function with base 10.
    // A value of 0 for the analogWrite turns the led off, that is visually not nice.
    // Therefor the result for the PWM is calculated to 1...255.

    float s = sin( rad);                  // The sine from radians
    float t = (0.5 * s) + 0.5;            // convert -1...1 to 0...1 for the logarithmic/exponential scale
    float u = pow( 10, t);                // convert 0...1 to 1...10 with exponential scale with base 10
    float v = (254.5 / 9.0 * (u - 1.0)) + 1.0; // convert 1...10 to 1...255. Add 0.5 to 254 for rounding
    int pwm = int( v);                    // convert it to integer for the PWM value

    rad += rad_increment;
    if( rad >= 2.0 * M_PI)
    {
      rad -= 2.0 * M_PI;
    }

    analogWrite( ledPin, pwm);
  }
}
