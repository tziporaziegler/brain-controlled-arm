/**
 * Description: Grabs brain data from the serial RX pin and sends CSV out over the TX pin (Half duplex.)             
 *              Moves an arm based on the attention and meditation values.
 * Author:      Tzipora Ziegler
 */

#include <SoftwareSerial.h>
#include <Brain.h> // https://github.com/kitschpatrol/Brain

// Radio module imports
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "AttMedHelpers.h"
#include "BrainWaves.h"
#include "Arm.h"

SoftwareSerial Serial1(10, 11); // RX, TX

// Set up the brain parser, pass it the serial object you want to listen on.
// For Arduino UNO, this should be the hardware serial. For Arduino Micro, this should be the software serial.
Brain brain(Serial1);

const double WAVE_LOW_THRESHOLD = 7.0;
const int NUM_BELOW_THRESHOLD_CUTOFF = 5;
BrainWaves brainWaves(WAVE_LOW_THRESHOLD);

//// These numbers should be calibrated to each individual.
//const int ATTENTION_THRESHOLD = 50;
//const int MEDITATION_THRESHOLD = 50;
AttMedHelpers attMedHelpers;

RF24 radio(5, 4); // CE, CSN
const byte address[6] = "00001";

Arm arm(radio);
 
void setup() {
  // Start the hardware serial.
  Serial.begin(9600);

  // Start the software serial. This is needed for Arduino Micro if using the RX pin.
  Serial1.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
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
      Serial.print("Num elements below threshold: ");
      Serial.println(brainWaves.recentNumElementsBelowThreshold1);
      if (brainWaves.recentNumElementsBelowThreshold1 > NUM_BELOW_THRESHOLD_CUTOFF && brainWaves.recentNumElementsBelowThreshold2 > NUM_BELOW_THRESHOLD_CUTOFF) {
        //      if (brainWaves.recentPercent1BelowThreshold() && brainWaves.recentPercent2BelowThreshold()) {
        arm.moveUp();
      } else if (brainWaves.recentNumElementsBelowThreshold1 < NUM_BELOW_THRESHOLD_CUTOFF && brainWaves.recentNumElementsBelowThreshold2 < NUM_BELOW_THRESHOLD_CUTOFF) {
        arm.moveDown();
      } else {
        // nothing happens if numElementsBelowThreshold equals cutoff or if two consecutive packets switch between attention and meditation states.
        arm.stay();
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

      Serial.println("");
    }
  }

  delay(10);
}
