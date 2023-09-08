#include <Arduino.h>
#include <EndlessPotentiometer.h>

#define PIN_A A0
#define PIN_B A1

// Uncomment for debug
#define DEBUG true
#define MAX_POT_VALUE 1023
#define POT_SENSITIVITY 1.5

int value1=0;
int value2=0;
int value=0;

EndlessPotentiometer pot;

void setup() {
  if (DEBUG) {
    Serial.begin(115200);
    pot.setSensitivity(POT_SENSITIVITY);
  }
}

void loop()
{
  pot.updateValues(analogRead(PIN_A), analogRead(PIN_B));

  if (pot.isMoving) {
    if (pot.direction == pot.CLOCKWISE) {
      value = value + pot.valueChanged;
    } else if (pot.direction == pot.COUNTER_CLOCKWISE) {
      value = value - pot.valueChanged;
    }

    if (value < 0) {
      value = 0;
    } else if (value > MAX_POT_VALUE) {
      value = MAX_POT_VALUE;
    }

    if (DEBUG) {
      Serial.print("Direction: ");
      Serial.print(pot.direction);
      Serial.print(" Value: ");
      Serial.print(value);
      Serial.print(" ValueChanged: ");
      Serial.println(pot.valueChanged);
    }
  }

  if (DEBUG) {
    delay(10);
  }
}
