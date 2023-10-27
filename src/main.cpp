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

  attachInterrupt(BUTTON, pause_play_button_pressed, FALLING);
}

void loop() {
  // on the first loop where the button has been pressed
  // TODO: will bounce be an issue here?
  if(!is_paused) {
    play_music(SPEAKER);
  } 

  delay(10);
}
