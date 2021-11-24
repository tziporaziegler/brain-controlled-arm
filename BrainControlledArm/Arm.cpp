#include "Arduino.h"
#include "Arm.h"

Arm::Arm() {}

void Arm::moveUp() {
  if (currentHeight < MAX_HEIGHT) {
      // TODO: Send 1 to servo
    currentHeight++;

    Serial.print("Arm moving up! New height: ");
    Serial.println(currentHeight);

    if (currentHeight == MAX_HEIGHT) {
      stop();
    }
  } else {
    Serial.println("Arm at max");
  }
}

void Arm::moveDown() {
  if (currentHeight > MIN_HEIGHT) {
      // TODO: Send -1 to servo
    currentHeight--;

    Serial.print("Arm moving down. New height: ");
    Serial.println(currentHeight);
  } else {
    Serial.println("Arm at min");
  }
}

void Arm::stay() {
  // TODO: Send 0 or nothing to servo
  Serial.println("Arm not moving");
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
