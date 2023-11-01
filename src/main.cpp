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

// TODO: change project files to .c and modify this file to match the example at https://community.platformio.org/t/use-c-instead-of-c/26768/6
void loop() { 
  if(!getIsPaused()) {
    playMusic(SPEAKER);
  }

  // NOTE: this is only needed on Wokwi to speed up simulation time
  // remove this line if running on 
  delay(10);
}
