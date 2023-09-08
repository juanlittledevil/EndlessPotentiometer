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
int localValue=0;
int altValue=0;

EndlessPotentiometer pot;

void setup() {
  if (DEBUG) {
    Serial.begin(115200);

    // You can modify the default parameters tho this is optional if you are happy with the default
    // Settings.
    pot.threshold = 3;      // Optional
    pot.sensitivity = 1.8;  // Optional
    pot.maxValue = 255;     // Optional
    pot.minValue = -255;    // Optional
  }
}

void loop()
{
  pot.updateValues(analogRead(PIN_A), analogRead(PIN_B));

  if (pot.isMoving) {
    // Use this method if you are controlling a single value with this pot. The object comes with its own
    // Internal value variable to keep track of.
    value = pot.value;

    // Or you can pass the value you want calculated. This is useful if all your values use the same
    // range.
    localValue = pot.getValue(localValue);

    // However, if you want to take advanatage of the relative nature of the component, you may
    // instead be interested in using the value changed instead. This will allow you to use the
    // same pot with different values ranges. But there is a few more lines of code needed.
    if (pot.direction == pot.CLOCKWISE) {
      altValue = altValue + pot.valueChanged;
    } else if (pot.direction == pot.COUNTER_CLOCKWISE) {
      altValue = altValue - pot.valueChanged;
    }

    if (altValue < 0) {
      altValue = 0;
    } else if (altValue > MAX_POT_VALUE) {
      altValue = MAX_POT_VALUE;
    }

    if (DEBUG) {
      Serial.print("direction: ");
      Serial.print(pot.direction);
      Serial.print(" value: ");
      Serial.print(value);
      Serial.print(" localValue: ");
      Serial.print(localValue);
      Serial.print(" altValue: ");
      Serial.print(altValue);
      Serial.print(" ValueChanged: ");
      Serial.println(pot.valueChanged);
    }
  }

  if (DEBUG) {
    delay(10);
  }
}
