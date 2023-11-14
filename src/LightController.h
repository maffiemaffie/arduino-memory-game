#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include "Arduino.h"

#define ON true
#define OFF false

/**
 * @brief Initialize all the pins and turn the lights off.
 * 
 */
void initLights();

/**
 * @brief Turn an LED on or off.
 * 
 * @param light The LED to set.
 * @param onOrOff What to set the LED to.
 */
void setLight(int light, bool onOrOff);

/**
 * @brief Turn an LED on for a specified length of time.
 * Pauses the program execution during delay.
 * 
 * @param light The LED to turn on.
 * @param delayMs The duration to keep the light on for.
 */
void setLightOnForDelay(int light, int delayMs);

#endif // LIGHTCONTROLLER_H