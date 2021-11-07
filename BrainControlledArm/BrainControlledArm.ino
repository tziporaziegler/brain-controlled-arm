/**
   Description: Grabs brain data from the serial RX pin and sends CSV out over the TX pin (Half duplex.)
   Moves an arm based on the attention and meditation values.
*/

#include <Brain.h>
#include <SoftwareSerial.h>
#include "AttMedHelpers.h"
#include "BrainWaves.h"
#include "Arm.h"

// Set up the brain parser, pass it the serial object you want to listen on.
// For Arduino UNO, this should be the hardware serial. For Arduino Micro, this should be the software serial.
Brain brain(Serial1);

const int WAVE_THRESHOLD = 10;
BrainWaves brainWaves(WAVE_THRESHOLD);

//// These numbers should be calibrated to each individual.
const int ATTENTION_THRESHOLD = 50;
const int MEDITATION_THRESHOLD = 50;
AttMedHelpers attMedHelpers;

Arm arm;

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

      brainWaves.update(brain.readPowerArray());
      int numElementsBelowThresholdAvg = brainWaves.getNumElementsBelowThresholdAvg();
      Serial.print("Num elements below threshold average: ");
      Serial.println(numElementsBelowThresholdAvg);
      if (numElementsBelowThresholdAvg > 5) {
        arm.moveUp();
      } else {
        arm.moveDown();
      }

      // Ensure the user has time to take a drink.
      if (arm.isStopped()) {
        Serial.println("Enjoy your drink!");
        delay(5000);
        arm.start();
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

      //      // Move the arm based on the meditation.
      //      if (meditationAvg > MEDITATION_THRESHOLD) {
      //        arm.moveUp();
      //      } else {
      //        arm.moveDown();
      //      }
    }
  }

  delay(10);
}
