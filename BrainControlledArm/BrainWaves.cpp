#include "BrainWaves.h"
#include "BrainWave.h"
#include <Arduino.h>

BrainWaves::BrainWaves() {}

void BrainWaves::update(unsigned long* powerArray) {
  double totalWavePercent = 0;

  const int numWaves = sizeof(powerArray);
  Serial.print("Num waves: ");
  Serial.println(numWaves);

  for (int i = 0; i < numWaves; i++) {
    BrainWave& wave = waves[i];
    const unsigned long newVal = powerArray[i];

    if (newVal == 0) {
      Serial.print("Bad data for the following wave: ");
      Serial.println(wave.getLabel());
      return;
    }

    wave.update(newVal);
    wave.printPercentStr();
    totalWavePercent += wave.getPercent();
  }

  double avgPercent = totalWavePercent / numWaves;
  Serial.print("Wave Percent Average: ");
  Serial.println(avgPercent);
  updateRecentPercentVals(avgPercent);
}

double BrainWaves::calculateRecentPercentAvg() {
  return (recentPercent1 + recentPercent2 + recentPercent3) / 3.0;
}

void BrainWaves::updateRecentPercentVals(double newVal) {
  recentPercent3 = recentPercent2;
  recentPercent2 = recentPercent1;
  recentPercent1 = newVal;
}
