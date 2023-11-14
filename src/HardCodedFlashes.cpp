#include "HardCodedFlashes.h";

void doStartSequence(int piezo) {
  int noteScale[] = {262, 294, 330, 370, 415, 466, 523/*, 587, 659, 740, 831, 932, 1046*/};
  int noteLength = 100;

  for (int measure = 0; measure < 3; measure++) {
    for (int beat = 0; beat < 4; beat++) {
      tone(piezo, noteScale[measure + beat], noteLength);
      setLightOnForDelay(beat, noteLength);
      noTone(piezo);
    }
  }

  tone(piezo, noteScale[6], 400);
  for (int i = 0; i < 4; i++) setLight(i, ON);
  delay(800);
  for (int i = 0; i < 4; i++) setLight(i, OFF);
  delay(400);
}

void doEndSequence(int piezo) {
  int noteScale[] = {349, 330, 311, 294};
  int noteLength = 200;

  for (int i = 0; i < 4; i++) {
    setLight(i, ON);
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      tone(piezo, noteScale[i], noteLength - 10);
      delay(noteLength);
      noTone(piezo);
    }
    setLight(i, OFF);
  }
}