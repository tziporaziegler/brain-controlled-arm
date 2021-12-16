#include "Arduino.h"
#include "Arm.h"
#include <RF24.h>

Arm::Arm(RF24 radio) {
  this->radio = radio;
}

void Arm::moveUp() {
  if (currentServoAngle < MAX_SERVO_ANGLE) {
    // To allow for gradual stepped movement, change this to currentServoAngle += interval.
    currentServoAngle = MAX_SERVO_ANGLE;
    
    move();

    Serial.print("Arm moving up! New height: ");
    Serial.println(currentServoAngle);

    if (currentServoAngle == MAX_SERVO_ANGLE) {
      stop();
    }
  } else {
    Serial.println("Arm at max");
  }
}

void Arm::moveDown() {
  if (currentServoAngle > MIN_SERVO_ANGLE) {
    // To allow for gradual stepped movement, change this to currentServoAngle -= interval.
    currentServoAngle = MIN_SERVO_ANGLE;
    
    move();

    Serial.print("Arm moving down. New height: ");
    Serial.println(currentServoAngle);
  } else {
    Serial.println("Arm at min");
  }
}

void Arm::move() {
  radio.write(&currentServoAngle, sizeof(currentServoAngle));
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
