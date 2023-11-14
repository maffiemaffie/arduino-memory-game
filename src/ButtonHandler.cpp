#include "ButtonHandler.h"

void ButtonHandler::update(int currentPressed) {
  if (activeButton == -1 && currentPressed == -1) return; // no button pressed
  
  // button stays down
  if (activeButton == currentPressed) {
    whileDownHandler(activeButton);  
    return;
  }

  // get the release if a button was pressed before
  if (activeButton != -1) {
    onReleaseHandler(activeButton);
  }

  // get the press if a new button was pressed
  if (currentPressed != -1) {
    onPressHandler(currentPressed);
  }

  // update active
  activeButton = currentPressed;
}
void ButtonHandler::registerOnPress(void (*onPress)(int)) {
  onPressHandler = onPress;
}

void ButtonHandler::registerOnRelease(void (*onRelease)(int)) {
  onReleaseHandler = onRelease;
}

void ButtonHandler::registerWhileDown(void (*whileDown)(int)) {
  whileDownHandler = whileDown;
}

int ButtonHandler::activeButton = -1;
void (*ButtonHandler::onPressHandler)(int) = nullptr;
void (*ButtonHandler::onReleaseHandler)(int) = nullptr;
void (*ButtonHandler::whileDownHandler)(int) = nullptr;