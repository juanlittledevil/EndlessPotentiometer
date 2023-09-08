#include <EndlessPotentiometer.h>
#include <Arduino.h>

EndlessPotentiometer::EndlessPotentiometer() {
  valueA = 0;
  valueB = 0;
  valueChanged = 0;
}

void EndlessPotentiometer::updateValues(int valueA, int valueB) {
  previousValueA = this->valueA;
  previousValueB = this->valueB;
  this->valueA = valueA;
  this->valueB = valueB;

  // decode each wiper value direction.
  if (valueA > (previousValueA + threshold)) {
    dirA = 1;
  } else if (valueA < (previousValueA - threshold)) {
    dirA = -1;
  } else {
    dirA = 0;
  }

  if (valueB > (previousValueB + threshold)) {
    dirB = 1;
  } else if (valueB < (previousValueB - threshold)) {
    dirB = -1;
  } else {
    dirB = 0;
  }

  // Now evaluate the actual direction of the pot.
  if (dirA == -1 && dirB == -1) {
    if (valueA > valueB) {
      direction = CLOCKWISE;
    } else {
      direction = COUNTER_CLOCKWISE;
    }
  } else if (dirA == 1 && dirB == 1) {
    if (valueA < valueB) {
      direction = CLOCKWISE;
    } else {
      direction = COUNTER_CLOCKWISE;
    }
  } else if (dirA == 1 && dirB == -1) {
    if ((valueA > (adcMaxValue / 2)) || (valueB > (adcMaxValue / 2))) {
      direction = CLOCKWISE;
    } else {
      direction = COUNTER_CLOCKWISE;
    }
  } else if (dirA == -1 && dirB == 1) {
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
}

// Threshold is the amount of change that must happen in order to be considered
// as a change in value. Ideally this should be set low but just large enough to
// catch jitter from the pot. 3 was a good value in my tests.
void EndlessPotentiometer::setThreshold(int threshold) {
  this->threshold = threshold;
}

// Sensitivity refers to how quickly values change when the knob is turned.
// Higher values will make it less sensitivy thus, needing to turn the knob more times
// until to reach the max or min values.
// If you are working with 127 values, a larger number may be desired. However,
// if you are workign with larger values you will want to set this lower.
void EndlessPotentiometer::setSensitivity(float sensitivity) {
  this->sensitivity = sensitivity;
}