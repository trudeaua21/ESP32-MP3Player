#include <Arduino.h>
#include "music.h"
#include "controller.h"
#include "ioConfig.h"
#include "soc/soc.h"
#include "esp_intr_alloc.h"

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
