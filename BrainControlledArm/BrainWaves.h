#ifndef BrainWaves_h
#define BrainWaves_h

#include "BrainWave.h"

class BrainWaves {
  private:
    BrainWave waves[8] = {("delta"), ("theta"), ("low alpha"), ("high alpha"), ("low beta"), ("high beta"), ("low gamma"), ("high gamma")};

    double recentPercent1 = 100;
    double recentPercent2 = 100;
    double recentPercent3 = 100;

    double percentThreshold;

    void updateRecentNumWavesBelowThreshold(int newVal);
    void updateRecentPercentVals(double newVal);
    double getRecentPercentAvg() ;

  public:
    double recentNumElementsBelowThreshold1 = 0;
    double recentNumElementsBelowThreshold2 = 0;
    double recentNumElementsBelowThreshold3 = 0;
    
    BrainWaves(double percentThreshold);

    void update(unsigned long* powerArray);
    double getNumElementsBelowThresholdAvg();
    bool percentAvgAboveThreshold();

    bool recentPercent1BelowThreshold();
    bool recentPercent2BelowThreshold();
};

#endif
