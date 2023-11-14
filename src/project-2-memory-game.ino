#include "ButtonHandler.h"
#include "MemoryGame.h"
#include "LightController.h"
#include "HardCodedFlashes.h"

using namespace std;

int buttonPin = A0;
int piezoPin = 6;
int pitchFrequencies[] = {370, 466, 554, 740};
int ladderValues[] = {785, 851, 929, 1023};
int noiseThreshold = 10;
int pressedDuration = 0;
bool listeningForInput = false;
State gameState;
MemoryGame game;

const int LIGHT_DELAY = 500;

void setup() {
  srand(analogRead(A1)); // disconnected pin
  initLights();

  game.registerNewPatternObserver(&displayPattern);
  game.registerChangedStateObserver(&changeState);
  game.registerGameEndedObserver(&gameOver);
  ButtonHandler::registerOnPress(&onPress);
  ButtonHandler::registerOnRelease(&onRelease);
  ButtonHandler::registerWhileDown(&whileDown);

  // do start stuff
  doStartSequence(piezoPin);
  game.start();
}

void loop() {
  int buttonValue = analogRead(buttonPin);
  int buttonPressed = whichButton(buttonValue);
  ButtonHandler::update(buttonPressed);
}

/**
 * @brief Display the pattern to the player using the LEDs and piezo.
 * 
 * @param event The event containing the new pattern.
 */
void displayPattern(NewPatternEventArgs event) {
  listeningForInput = false;
  delay(LIGHT_DELAY);
  for (int i = 0; i < event.pattern->length; i++) {
    // emit sound maybe
    delay(100);
    tone(piezoPin, pitchFrequencies[event.pattern->values[i]], LIGHT_DELAY);
    setLightOnForDelay(event.pattern->values[i], LIGHT_DELAY);

  }
  listeningForInput = true;
}

/**
 * @brief Handles a changed game state.
 * 
 * @param event The event containing the updated game state.
 */
void changeState(ChangedStateEventArgs event) {
  gameState = event.state;
  if (event.state != Active) listeningForInput = false;
  else listeningForInput = true;
}

/**
 * @brief Ends the game.
 * 
 * @param event The event containing the final score.
 */
void gameOver(GameEndedEventArgs event) {
  doEndSequence(piezoPin);
}

/**
 * @brief Handles a button press.
 * 
 * @param button The pressed button.
 */
void onPress(int button) {
  if (!listeningForInput) return; // bro
  tone(piezoPin, pitchFrequencies[button], LIGHT_DELAY / 2);
  setLight(button, ON);
}

/**
 * @brief Handles a button release.
 * 
 * @param button The released button.
 */
void onRelease(int button) {
  setLight(button, OFF);
  int thisDuration = pressedDuration;
  pressedDuration = 0;

  if (gameState == Ending) {
    doStartSequence(piezoPin);
    game.start();
    return;
  }
  if (!listeningForInput) return; // bro
  if (thisDuration < noiseThreshold) return; // filter out ghost presses
  game.input(button);
}

/**
 * @brief Handles an actively pressed button.
 * 
 * @param button The pressed button.
 */
void whileDown(int button) {
  pressedDuration++;
}

/**
 * @brief Decodes the pressed button from the ladder voltage.
 * 
 * @param readValue The value at the end of the resistor ladder.
 * @return int The pressed button or -1 if no button pressed.
 */
int whichButton(int readValue) {
  int ladderThreshold = 5;
  if (readValue == 0) return -1;
  for (int i = 0; i < 4; i++) {
    if (abs(readValue-ladderValues[i]) < ladderThreshold) return i;
  }
}