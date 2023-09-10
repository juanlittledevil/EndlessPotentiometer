// EndlessPotentiometer.h

#ifndef EndlessPotentiometer_h
#define EndlessPotentiometer_h

#include "Arduino.h"

class EndlessPotentiometer {
public:
  enum Direction {
    NOT_MOVING,
    CLOCKWISE,
    COUNTER_CLOCKWISE
  };

  bool isMoving;
  int value;          // Internal variable to hold a pot value.
  int direction;      // Which direction the knob is being turned.
  int valueChanged;   // This is the amount of change between last collection and this current one.

  // Threshold is the amount of change that must happen in order to be considered
  // as a change in value. Ideally this should be set low but just large enough to
  // catch jitter from the pot. 3 was a good value in my tests.
  int threshold = 3;

  // Sensitivity refers to how quickly values change when the knob is turned.
  // Higher values will make it less sensitivy thus, needing to turn the knob more times
  // until to reach the max or min values.
  // If you are working with 127 values, a larger number may be desired. However,
  // if you are workign with larger values you will want to set this lower.
  float sensitivity = 8;

  // Sets the max value range. That the internal max value can be set to. The
  // default is 127, but this can be scaled ot anything you want.
  int maxValue = 127;

  // Sets the min value for the range. can be anything as long as it is less than maxValue
  int minValue = 0;

  EndlessPotentiometer();

  // You MUCT include this in your loop() function, and it must be called before accessing any other
  // variable of method from this library in your sketch.
  void updateValues(int valueA, int valueB);

  // Use your own value instead of the internal one.
  int getValue(int value);

private:
  enum IndividualDirection {
    UP = 1,
    DOWN = -1
  };

  int valueA;
  int valueB;
  int previousValueA = 0;
  int previousValueB = 0;
  int dirA = 0;
  int dirB = 0;
  const int adcMaxValue = 1023;  // the max value from analogRead for each pin.
};

#endif
