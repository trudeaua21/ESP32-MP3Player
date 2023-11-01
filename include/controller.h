#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>

extern bool getIsPaused();
extern int getCurrentSongIndex();

extern void IRAM_ATTR pausePlayButtonPressed();
extern void IRAM_ATTR nextSongButtonPressed();
extern void IRAM_ATTR prevSongButtonPressed();

#endif