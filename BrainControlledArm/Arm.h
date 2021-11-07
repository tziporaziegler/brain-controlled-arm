#ifndef Arm_h
#define Arm_h

class Arm {
  private:
    const int MIN_HEIGHT = 0;
    const int MAX_HEIGHT = 10;
    int currentHeight = 0;
    bool stopped = false;

    // For now, use LEDs to represent the arm movement.
    // Green = up. Red = down.
    const int GREEN_LED_PIN = 9;
    const int RED_LED_PIN = 5;

  public:
    Arm();

    void moveUp();
    void moveDown();

    void start();
    void stop();
    bool isStopped();
};

#endif
