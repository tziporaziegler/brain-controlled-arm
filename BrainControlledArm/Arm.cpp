#include "Arduino.h"
#include "Arm.h"

Arm::Arm() {
  pinMode(LED_PIN, OUTPUT);
}

void Arm::moveUp() {
  if (currentHeight < MAX_HEIGHT) {
    digitalWrite(LED_PIN, HIGH);
    currentHeight++;

    Serial.print("Arm moving up! New height: ");
    Serial.println(currentHeight);

    if (currentHeight == MAX_HEIGHT) {
      stop();
    }
  }
}

void Arm::moveDown() {
  if (currentHeight > MIN_HEIGHT) {
    digitalWrite(LED_PIN, LOW);
    currentHeight--;
    
    Serial.print("Arm moving down. New height: ");
    Serial.println(currentHeight);
  }
}

void Arm::start() {
  stopped = false;
}

void Arm::stop() {
  stopped = true;
}

bool Arm::isStopped() {
  return stopped;
}
