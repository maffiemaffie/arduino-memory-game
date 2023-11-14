#include "LightController.h";

int ledPins[] = {2, 3, 4, 5};

void initLights() {
  for (int pin : ledPins) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
}

void setLight(int light, bool onOrOff) {
  digitalWrite(ledPins[light], onOrOff ? HIGH : LOW);
}

void setLightOnForDelay(int light, int delayMs) {
  setLight(light, ON);
  delay(delayMs);
  setLight(light, OFF);
}