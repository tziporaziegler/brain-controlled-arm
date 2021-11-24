#ifndef Arm_h
#define Arm_h

class Arm {
  private:
    const int MIN_HEIGHT = 0;
    const int MAX_HEIGHT = 10;
    int currentHeight = 0;
    bool stopped = false;

  public:
    Arm();

    void moveUp();
    void moveDown();
    void stay();

    void start();
    void stop();
    bool isStopped();
};

#endif
