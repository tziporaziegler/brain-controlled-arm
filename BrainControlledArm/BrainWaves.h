#ifndef BrainWaves_h
#define BrainWaves_h

#include "BrainWave.h"

class BrainWaves {
  private:
    BrainWave waves[8] = {("delta"), ("theta"), ("low alpha"), ("high alpha"), ("low beta"), ("high beta"), ("low gamma"), ("high gamma")};

    double recentPercent1 = 100.0;
    double recentPercent2 = 100.0;
    double recentPercent3 = 100.0;

    void updateRecentPercentVals(double newVal);

  public:
    BrainWaves();

    void update(unsigned long* powerArray);
    double calculateRecentPercentAvg();
};

#endif
