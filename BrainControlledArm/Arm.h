#ifndef Arm_h
#define Arm_h

#include <Arduino.h>

class Arm {
  private:
    const int minHeight = 0;
    const int maxHeight = 10;
    int currentHeight = 0;

    // For now, use an LED to represent the arm movement.
    const int ledPin = 4;

  public:
    Arm();

    void moveUp();
    void moveDown();
    bool atMaxHeight();
};

#endif
