/**
   Description: Grabs brain data from the serial RX pin and sends CSV out over the TX pin (Half duplex.)
   Moves an arm based on the attention and meditation values.
*/

#include <Brain.h>
#include <SoftwareSerial.h>
#include "AttMedHelpers.h"
#include "BrainWave.h"
#include "Arm.h"

// Set up the brain parser, pass it the serial object you want to listen on.
// For Arduino UNO, this should be the hardware serial. For Arduino Micro, this should be the software serial.
Brain brain(Serial1);

Arm arm;
AttMedHelpers attMedHelpers;

const double waveThreshold = 25;

double recentWavePercent1 = 100.0;
double recentWavePercent2 = 100.0;
double recentWavePercent3 = 100.0;

// These numbers should be calibrated to each individual.
const double attentionThreshold = 50;
const double meditationThreshold = 50;

BrainWave waves[] = {("delta"), ("theta"), ("low alpha"), ("high alpha"), ("low beta"), ("high beta"), ("low gamma"), ("high gamma")};

void setup() {
  // Start the hardware serial.
  Serial.begin(9600);

  // Start the software serial. This is needed for Arduino Micro if using the RX pin.
  Serial1.begin(9600);
}

void loop() {
  if (Serial1.available() > 0) {
    // Expect packets about once per second.
    // The readCSV() function returns a string (well, char*) listing the most recent brain data, in the following format:
    // "signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma"
    if (brain.update()) {
      Serial.println(brain.readErrors());
      Serial.println(brain.readCSV());

      if (brain.readSignalQuality() != 0) {
        Serial.println("Bad signal quality.");
        return;
      }

      int totalWavePercent = 0;

      unsigned long* powerArray = brain.readPowerArray();
      const int numWaves = sizeof(powerArray);
      for (int i = 0; i < numWaves; i++) {
        BrainWave wave = waves[i];
        const char* label = wave.getLabel();

        const unsigned long newVal = powerArray[i];

        if (newVal == 0) {
          Serial.print("Bad data for the following wave: ");
          Serial.println(label);
          return;
        }

        wave.update(newVal);

        const double wavePercent = wave.getPercent();
        printPercentStr(label, newVal, wave.getMaxVal(), wavePercent);
        totalWavePercent += wavePercent;
      }

      double avgPercent = totalWavePercent / double(numWaves);
      Serial.print("Percent Average: ");
      Serial.println(avgPercent);
      updateRecentMeditationVals(avgPercent);
      const double recentWavePercentAvg = calculateRecentWavePercentAvg();

      if (recentWavePercentAvg < waveThreshold) {
        arm.moveUp();
      } else {
        arm.moveDown();
      }

      // Ensure the user has time to take a drink.
      if (arm.atMaxHeight()) {
        Serial.println("Enjoy your drink!");
        delay(5000);
      }

      int attentionVal = brain.readAttention();
      int meditationVal = brain.readMeditation();
      if (attentionVal == 0 || meditationVal == 0) {
        Serial.println("Bad attention or meditation data.");
        return;
      }

      attMedHelpers.updateRecentAttentionVals(attentionVal);
      attMedHelpers.updateRecentMeditationVals(meditationVal);

      // Use the average of 3 packets instead of a single packet to increase reliablity.
      double attentionAvg = attMedHelpers.calculateRecentAttentionAvg();
      Serial.print("Attention Average: ");
      Serial.println(attentionAvg);

      double meditationAvg = attMedHelpers.calculateRecentMeditationAvg();
      Serial.print("Meditation Average: ");
      Serial.println(meditationAvg);

      // Move the arm based on the meditation.
      //      if (meditationAvg > meditationThreshold) {
      //        arm.moveUp();
      //      } else {
      //        arm.moveDown();
      //      }
    }
  }
}

void printPercentStr(const char* label, unsigned long newVal, unsigned long maxVal, double percent) {
  Serial.print(label);
  Serial.print(": ");
  Serial.print(newVal);
  Serial.print("/");
  Serial.print(maxVal);
  Serial.print(" = ");
  Serial.print(percent);
  Serial.println("%");
}

void updateRecentMeditationVals(double newVal) {
  recentWavePercent3 = recentWavePercent2;
  recentWavePercent2 = recentWavePercent1;
  recentWavePercent1 = newVal;
}

double calculateRecentWavePercentAvg() {
  return (recentWavePercent1 + recentWavePercent2 + recentWavePercent3) / 3;
}
