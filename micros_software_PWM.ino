// ---------------------------------------------
// micros_software_PWM.ino
// ---------------------------------------------
// License: The Unlicense, Public Domain.
// Author: Koepel
// 2019 april 16
// ---------------------------------------------
// 
// Use micros() to generate a PWM signal in software
// to set the brightness of a led on any digital pin.
// The pin does not have to be a PWM capable pin.
//
// The brightness can be entered with the serial monitor.
//
// The PWM value for the brightness is 0...255
// The lowest value is 0 (the output will be constant LOW).
// The highest value is 255 (the output will be contant HIGH).
//
// The minimum pulse width is set to 70 microseconds.
// With that value the brightness of the dimmed led is almost
// without visual flicker.
//
// The LED_BUILTIN is the led on the Arduino board,
// any other digital pin can be used.


const int pinLed = LED_BUILTIN;  // The digital pin to which a led is connected.

unsigned long previousMicros;
unsigned long interval;
int outputState;

const int pwmMinimumWidth = 70;  // minimum pulse width in microseconds

int pwmValue = 10;               // pwm value to start with (0...255)

void setup()
{
  Serial.begin( 9600);
  Serial.setTimeout( 10);
  Serial.println( "Enter brightness, 0...255");
  
  pinMode( pinLed, OUTPUT);
}

void loop()
{
  unsigned long currentMicros = micros();

  if( Serial.available() > 0)
  {
    if( isdigit( Serial.peek()))                 // is it a decimal digit ?
    {
      int brightness = Serial.parseInt();        // get the number
      pwmValue = constrain( brightness, 0, 255);  // set the new PWM value
    }
    else
    {
      Serial.read();      // read unwanted character from serial port and discard it.
    }
  }

  if( currentMicros - previousMicros >= interval)
  {
    previousMicros = currentMicros;
    
    if( outputState == LOW && pwmValue != 0)
    {
      digitalWrite( pinLed, HIGH);
      outputState = HIGH;
      interval = pwmMinimumWidth * pwmValue;  // the time that the signal will be HIGH.
    }
    else if( outputState == HIGH && pwmValue != 255)
    {
      digitalWrite( pinLed, LOW);
      outputState = LOW;
      interval = pwmMinimumWidth * (255 - pwmValue); // the time that the signal will be LOW.
    }
  }
}
