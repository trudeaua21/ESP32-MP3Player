#include <Arduino.h>
#include "music.h"
#include "controller.h"

#define SPEAKER 2
#define PAUSE_PLAY_BUTTON 12
#define NEXT_SONG_BUTTON 13
#define PREV_SONG_BUTTON 14

void setup() {
  pinMode(SPEAKER, OUTPUT);
  pinMode(PAUSE_PLAY_BUTTON, INPUT_PULLUP);
  pinMode(NEXT_SONG_BUTTON, INPUT_PULLUP);
  pinMode(PREV_SONG_BUTTON, INPUT_PULLUP);

  attachInterrupt(PAUSE_PLAY_BUTTON, pausePlayButtonPressed, FALLING);
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
