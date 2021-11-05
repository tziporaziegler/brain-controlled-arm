#include "Arduino.h"
#include "Arm.h"

Arm::Arm() {
  pinMode(ledPin, OUTPUT);
}

void Arm::moveUp() {
  if (currentHeight < maxHeight) {
    Serial.println("Arm moving up!");
    digitalWrite(ledPin, HIGH);
    currentHeight++;
    Serial.print("New height: ");
    Serial.println(currentHeight);
  }
}

void Arm::moveDown() {
  if (currentHeight > minHeight) {
    Serial.println("Arm moving down.");
    digitalWrite(ledPin, LOW);
    currentHeight--;
    Serial.print("New height: ");
    Serial.println(currentHeight);
  }
}

bool Arm::atMaxHeight() {
  return currentHeight == maxHeight;
}
