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
