#ifndef Arm_h
#define Arm_h

#include <RF24.h>

class Arm {
  private:
    const int MIN_SERVO_ANGLE = 30;
    const int MAX_SERVO_ANGLE = 160;
    int currentServoAngle = 30;
    bool stopped = false;
    RF24 radio;

    void move();

  public:
    Arm(RF24 radio);

    void moveUp();
    void moveDown();
    void stay();

    void start();
    void stop();
    bool isStopped();
};

#endif
