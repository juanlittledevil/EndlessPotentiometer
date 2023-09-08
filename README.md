# EndlessPotentiometer.h


This library is based on Bjørn Brandal's work [here](https://hackaday.io/project/171841-driveralgorithm-for-360-deg-endless-potentiometer).
It is a library for detecting the direction and values from an endless rotary potentiometer like those found on the Novation Circuit and
the Native Instruments KORE/KORE2 controllers.

The library has purposely left out the Arduino library so that it can be framework-agnostic. This means
that if you want to use a library like Mozzi, it'll still work since it evaluates the values passed and not by calling those values itself using analogRead().


> Here is an example of how to use this:

```
#include <Arduino.h>
#include <EndlessPotentiometer.h>

#define PIN_A A0
#define PIN_B A1

// Uncomment for debug
#define DEBUG true
#define MAX_POT_VALUE 1023

int value1=0;
int value2=0;
int value=0;

EndlessPotentiometer pot;

void setup() {
  if (DEBUG) {
    Serial.begin(115200);
  }
}

void loop()
{
  pot.updateValues(analogRead(PIN_A), analogRead(PIN_B));

  if (pot.isMoving()) {
    if (pot.direction == 1 && value < MAX_POT_VALUE) {
      value++;
    } else if (pot.direction == 2 && value > 0) {
      value--;
    }

    if (DEBUG) {
      Serial.print("Direction: ");
      Serial.print(pot.direction);
      Serial.print(" Value: ");
      Serial.println(value);
    }
  }

  if (DEBUG) {
    delay(10);
  }
}
```
