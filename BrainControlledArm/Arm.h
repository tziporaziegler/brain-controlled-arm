#ifndef Arm_h
#define Arm_h

class Arm {
  private:
    const int MIN_HEIGHT = 0;
    const int MAX_HEIGHT = 10;
    int currentHeight = 0;
    bool stopped = false;

    // For now, use an LED to represent the arm movement.
    const int LED_PIN = 4;

  public:
    Arm();

    void moveUp();
    void moveDown();

    void start();
    void stop();
    bool isStopped();
};

#endif
