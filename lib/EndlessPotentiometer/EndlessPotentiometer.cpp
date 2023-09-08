#include "EndlessPotentiometer.h"

EndlessPotentiometer::EndlessPotentiometer() {
  valueA = 0;
  valueB = 0;
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
}

bool EndlessPotentiometer::isMoving() {
  if (direction == NOT_MOVING) {
    return false;
  } else {
    return true;
  }
}

void EndlessPotentiometer::setThreshold(int threshold) {
  this->threshold = threshold;
}