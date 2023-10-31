#include <Arduino.h>
#include "music.h"
#include "state.h"

#define SPEAKER 2
#define BUTTON 12
#define UNPRESSED HIGH
#define PRESSED LOW

void setup() {
  pinMode(SPEAKER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  attachInterrupt(BUTTON, pausePlayButtonPressed, FALLING);
}

void loop() { 
  if(!getIsPaused()) {
    play_music(SPEAKER);
  }

  delay(10);
}
