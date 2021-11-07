#include "BrainWave.h"
#include <Arduino.h>

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

double BrainWave::getPercent() {
  return latestVal / (double)maxVal * 100;
}

void BrainWave::printPercentStr() {
  Serial.print(label);
  Serial.print(": ");
  Serial.print(latestVal);
  Serial.print("/");
  Serial.print(maxVal);
  Serial.print(" = ");
  Serial.print(getPercent());
  Serial.println("%");
}
