#ifndef BrainWave_h
#define BrainWave_h

#include <Arduino.h>

class BrainWave {
  private:
    const char* label;
    unsigned long latestVal;
    unsigned long maxVal = 0;

  public:
    BrainWave(const char* label);
    
    void update(unsigned long newVal);

    const char* getLabel();
    unsigned long getMaxVal();
    
    double getPercent();  
};

#endif
