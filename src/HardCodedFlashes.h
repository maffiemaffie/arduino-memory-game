#include "LightController.h";
#include "Arduino.h";

/**
 * @brief Runs the start light/music sequence.
 * 
 * @param piezo The pin connected to the piezo.
 */
void doStartSequence(int piezo);

/**
 * @brief Run the end light/music sequence.
 * 
 * @param piezo The pin connected to the piezo.
 */
void doEndSequence(int piezo);