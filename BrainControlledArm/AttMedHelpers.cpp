#include "AttMedHelpers.h"

AttMedHelpers::AttMedHelpers() {}

void AttMedHelpers::updateRecentAttentionVals(int newVal) {
  recentAttentionVal3 = recentAttentionVal2;
  recentAttentionVal2 = recentAttentionVal1;
  recentAttentionVal1 = newVal;
}

void AttMedHelpers::updateRecentMeditationVals(int newVal) {
  recentMeditationVal3 = recentMeditationVal2;
  recentMeditationVal2 = recentMeditationVal1;
  recentMeditationVal1 = newVal;
}

double AttMedHelpers::calculateRecentAttentionAvg() {
  return (recentAttentionVal1 + recentAttentionVal2 + recentAttentionVal3) / 3.0;
}

double AttMedHelpers::calculateRecentMeditationAvg() {
  return (recentMeditationVal1 + recentMeditationVal2 + recentMeditationVal3) / 3.0;
}
