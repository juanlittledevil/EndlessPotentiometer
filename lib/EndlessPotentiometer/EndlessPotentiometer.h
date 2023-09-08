// EndlessPotentiometer.h

#ifndef EndlessPotentiometer_h
#define EndlessPotentiometer_h

class EndlessPotentiometer {
public:
  enum Direction {
    NOT_MOVING,
    CLOCKWISE,
    COUNTER_CLOCKWISE
  };

  int direction;
  int threshold = 3; // jitter threshold. used to know when the knob is being moved.
  
  EndlessPotentiometer();

  void updateValues(int valueA, int valueB);
  bool isMoving();
  void setThreshold(int threshold);

private:
  int valueA;
  int valueB;
  int previousValueA = 0;
  int previousValueB = 0;
  int dirA = 0;
  int dirB = 0;
  const int adcMaxValue = 1023;  // the max value from analogRead for each pin.
};

#endif
