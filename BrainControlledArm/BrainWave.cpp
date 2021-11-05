#include "Arduino.h"
#include "BrainWave.h"

BrainWave::BrainWave(const char* label) {
  this->label = label;
}

void BrainWave::update(unsigned long newVal) {
  latestVal = newVal;
  maxVal = max(maxVal, newVal);
}

const char* BrainWave::getLabel() {
  return label;
}

unsigned long BrainWave::getMaxVal() {
  return maxVal;
}

double BrainWave::getPercent() {
  return latestVal / maxVal * 100;
}
