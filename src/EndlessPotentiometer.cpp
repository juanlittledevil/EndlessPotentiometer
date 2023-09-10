#include <EndlessPotentiometer.h>
#include <Arduino.h>

EndlessPotentiometer::EndlessPotentiometer() {
  valueA = 0;
  valueB = 0;
  valueChanged = 0;
  value = 0;
}

void EndlessPotentiometer::updateValues(int valueA, int valueB) {
  previousValueA = this->valueA;
  previousValueB = this->valueB;
  this->valueA = valueA;
  this->valueB = valueB;

  // decode each wiper value direction.
  if (valueA > (previousValueA + threshold)) {
    dirA = UP;
  } else if (valueA < (previousValueA - threshold)) {
    dirA = DOWN;
  } else {
    dirA = NOT_MOVING;
  }

  if (valueB > (previousValueB + threshold)) {
    dirB = UP;
  } else if (valueB < (previousValueB - threshold)) {
    dirB = DOWN;
  } else {
    dirB = NOT_MOVING;
  }

  // Now evaluate the actual direction of the pot.
  if (dirA == DOWN && dirB == DOWN) {
    if (valueA > valueB) {
      direction = CLOCKWISE;
    } else {
      direction = COUNTER_CLOCKWISE;
    }
  } else if (dirA == UP && dirB == UP) {
    if (valueA < valueB) {
      direction = CLOCKWISE;
    } else {
      direction = COUNTER_CLOCKWISE;
    }
  } else if (dirA == UP && dirB == DOWN) {
    if ((valueA > (adcMaxValue / 2)) || (valueB > (adcMaxValue / 2))) {
      direction = CLOCKWISE;
    } else {
      direction = COUNTER_CLOCKWISE;
    }
  } else if (dirA == DOWN && dirB == UP) {
    if ((valueA < (adcMaxValue/2)) || (valueB < (adcMaxValue/2))) {
      direction = CLOCKWISE;
    } else {
      direction = COUNTER_CLOCKWISE;
    }
  } else {
    direction = NOT_MOVING;
  }
  
  // If we are not not dancing then we are dancing.
  if (direction == NOT_MOVING) {
    isMoving = false;
  } else {
    isMoving = true;
  }

  // Record the change.
  // Avoid values around zero and max as value has flat region. Instead use
  // the values in between which are more predictable and linear.
  if (dirA != NOT_MOVING && dirB != NOT_MOVING) {
    if ((valueA < adcMaxValue*0.8) && (valueA > adcMaxValue*0.2)) {
      valueChanged = direction*abs(valueA - previousValueA)/sensitivity;
    } else {
      valueChanged = direction*abs(valueB - previousValueB)/sensitivity;
    }
  }

  // Update the 
  value = getValue(value);
}


int EndlessPotentiometer::getValue(int value) {
  if (isMoving) {
    if (direction == CLOCKWISE) {
      value = value + valueChanged;
    } else if (direction == COUNTER_CLOCKWISE) {
      value = value - valueChanged;
    }

    if (value < minValue) {
      value = minValue;
    } else if (value > maxValue) {
      value = maxValue;
    }

    return value;
  }
}