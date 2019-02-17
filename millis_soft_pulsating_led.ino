// ---------------------------------------------
// millis_soft_pulsating_led.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 february 17
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
    // The sine wave is going through a logarithmic function to calculate the PWM value.
    // To get 0...1 out of the log function, the sine is converted to 1...10.
    // A value of 0 for the analogWrite turns the led off, that is visually not nice.
    // Therefor the result for the PWM is calculated to 1...255.

    float s = sin( rad);                  // The sine from radians
    float t = 5.5 + (4.5 * s);            // convert -1...1 to 1...10 for the log10
    float u = 1.0 + (254.0 * log10( t));  // convert 1...10 to 1...255 with log scale
    int pwm = int( u);                    // convert it to integer for the PWM value

    rad += rad_increment;
    if( rad >= 2.0 * M_PI)
    {
      rad -= 2.0 * M_PI;
    }

    analogWrite( ledPin, pwm);
  }
}
