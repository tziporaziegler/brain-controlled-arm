#ifndef BrainWaves_h
#define BrainWaves_h

#include "BrainWave.h"

class BrainWaves {
  private:
    BrainWave waves[8] = {("delta"), ("theta"), ("low alpha"), ("high alpha"), ("low beta"), ("high beta"), ("low gamma"), ("high gamma")};

    double recentNumElementsBelowThreshold1 = 0;
    double recentNumElementsBelowThreshold2 = 0;
    double recentNumElementsBelowThreshold3 = 0;

    double recentPercent1 = 100;
    double recentPercent2 = 100;
    double recentPercent3 = 100;

    int percentThreshold;

    void updateRecentNumWavesBelowThreshold(int newVal);
    void updateRecentPercentVals(double newVal);
    double getRecentPercentAvg() ;

  public:
    BrainWaves(int percentThreshold);

    void update(unsigned long* powerArray);
    double getNumElementsBelowThresholdAvg();
    bool percentAvgAboveThreshold();
};

#endif
