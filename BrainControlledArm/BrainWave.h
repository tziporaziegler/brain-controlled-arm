#ifndef BrainWave_h
#define BrainWave_h

class BrainWave {
  private:
    const char* label;
    unsigned long latestVal;
    unsigned long maxVal = 0;

  public:
    BrainWave(const char* label);
    
    void update(unsigned long newVal);

    const char* getLabel();
    
    double getPercent();  
    void printPercentStr();
};

#endif
