// Description: Grabs brain data from the serial RX pin and sends CSV out over the TX pin (Half duplex.)
// Moves an arm based on the attention and meditation values.

#include <Brain.h>
#include <SoftwareSerial.h>

// Set up the brain parser, pass it the serial object you want to listen on.
// For Arduino UNO, this should be the hardware serial. For Arduino Micro, this should be the software serial.
Brain brain(Serial1);

int recentAttentionVal1 = 0;
int recentAttentionVal2 = 0;
int recentAttentionVal3 = 0;

int recentMeditationVal1 = 0;
int recentMeditationVal2 = 0;
int recentMeditationVal3 = 0;

// These numbers should be calibrated to each individual.
double attentionThreshold = 50;
double meditationThreshold = 50;

// For now, use an LED to represent the arm movement.
int ledPin = 4;

void setup() {
  // Start the hardware serial.
  Serial.begin(9600);

  // Start the software serial. This is needed for Arduino Micro if using the RX pin.
  Serial1.begin(9600);

  pinMode(ledPin, OUTPUT);
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

      int attentionVal = brain.readAttention();
      int meditationVal = brain.readMeditation();
      if (attentionVal == 0 || meditationVal == 0) {
        Serial.println("Bad attention or meditation data.");
        return;
      }

      updateRecentAttentionVals(attentionVal);
      updateRecentMeditationVals(meditationVal);

      // Use the average of 3 packets instead of a single packet to increase reliablity.
      double attentionAvg = calculateRecentAttentionAvg();
      double meditationAvg = calculateRecentMeditationAvg();

      // Move the arm based on the meditation.
      if (meditationAvg > meditationThreshold) {
        moveArmUp();
      } else {
        moveArmDown();
      }
    }
  }
}

void updateRecentAttentionVals(int newVal) {
  recentAttentionVal3 = recentAttentionVal2;
  recentAttentionVal2 = recentAttentionVal1;
  recentAttentionVal1 = newVal;
}

void updateRecentMeditationVals(int newVal) {
  recentMeditationVal3 = recentMeditationVal2;
  recentMeditationVal2 = recentMeditationVal1;
  recentMeditationVal1 = newVal;
}

double calculateRecentAttentionAvg() {
  double average = (recentAttentionVal1 + recentAttentionVal2 + recentAttentionVal3) / 3.0;
  Serial.print("Attention Average: ");
  Serial.println(average);
  return average;
}

double calculateRecentMeditationAvg() {
  double average = (recentMeditationVal1 + recentMeditationVal2 + recentMeditationVal3) / 3.0;
  Serial.print("Meditation Average: ");
  Serial.println(average);
  return average;
}

void moveArmUp() {
  Serial.println("Arm moving up!");
  digitalWrite(ledPin, HIGH);
}

void moveArmDown() {
  Serial.println("Arm moving down.");
  digitalWrite(ledPin, LOW);
}
