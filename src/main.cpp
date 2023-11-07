#include <Arduino.h>
#include "music.h"
#include "controller.h"
#include "ioConfig.h"



void setup() {
  initIO();
}

// TODO: change project files to .c and modify this file to match the example at https://community.platformio.org/t/use-c-instead-of-c/26768/6
void loop() { 
  if(!getIsPaused()) {
    loadSongAtIndex(getCurrentSongIndex());
    playMusic(SPEAKER);
  }

  // NOTE: this is only needed on Wokwi to speed up simulation time
  // remove this line if running on 
  delay(10);
}
