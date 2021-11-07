#include "BrainWaves.h"
#include "BrainWave.h"
#include <Arduino.h>

BrainWaves::BrainWaves(const int percentThreshold) {
  this->percentThreshold = percentThreshold;
}

void BrainWaves::update(unsigned long* powerArray) {
  double totalWavePercent = 0;
  int numElementsBelowThreshold = 0;

  const int numWaves = 8; // sizeof(powerArray) / sizeof(*powerArray);
  //  Serial.print("Num waves: ");
  //  Serial.println(numWaves);

  for (int i = 0; i < numWaves; i++) {
    BrainWave& wave = waves[i];
    const unsigned long newVal = powerArray[i];

    if (newVal == 0) {
      Serial.print("Bad data for the following wave: ");
      Serial.println(wave.getLabel());
      return;
    }

    wave.update(newVal);
    double percent = wave.getPercent();
    wave.printPercentStr();
    totalWavePercent += percent;

    if (percent < percentThreshold) {
      numElementsBelowThreshold++;
    }
  }

  if (numWaves > 0) {
    double avgPercent = totalWavePercent / (double)numWaves;
    Serial.print("Wave Percent Average: ");
    Serial.println(avgPercent);
    updateRecentPercentVals(avgPercent);

    updateRecentNumWavesBelowThreshold(numElementsBelowThreshold);
  }
}

double BrainWaves::getNumElementsBelowThresholdAvg() {
  return (recentNumElementsBelowThreshold1 + recentNumElementsBelowThreshold2 + recentNumElementsBelowThreshold3) / 3.0;
}

bool BrainWaves::percentAvgAboveThreshold() {
  return getRecentPercentAvg() < percentThreshold;
}

void BrainWaves::updateRecentNumWavesBelowThreshold(int newVal) {
  recentNumElementsBelowThreshold3 = recentNumElementsBelowThreshold2;
  recentNumElementsBelowThreshold2 = recentNumElementsBelowThreshold1;
  recentNumElementsBelowThreshold1 = newVal;
}

void BrainWaves::updateRecentPercentVals(double newVal) {
  recentPercent3 = recentPercent2;
  recentPercent2 = recentPercent1;
  recentPercent1 = newVal;
}

double BrainWaves::getRecentPercentAvg() {
  return (recentPercent1 + recentPercent2 + recentPercent3) / 3.0;
}
