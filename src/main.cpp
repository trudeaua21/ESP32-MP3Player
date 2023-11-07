#include <Arduino.h>
#include "music.h"
#include "controller.h"
#include "ioConfig.h"

void setup() {
  initIO();
}

void loop() { 
  if(!getIsPaused()) {
    loadSongAtIndex(getCurrentSongIndex());
    playMusic(SPEAKER);
  }

  // NOTE: this is only needed on Wokwi to speed up simulation time
  // remove this line if running on 
  delay(10);
}
