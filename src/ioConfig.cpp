#include "ioConfig.h"
#include "controller.h"

#include <Arduino.h>

void initIO() {
    pinMode(SPEAKER, OUTPUT);
    pinMode(PAUSE_PLAY_BUTTON, INPUT_PULLUP);
    pinMode(NEXT_SONG_BUTTON, INPUT_PULLUP);
    pinMode(PREV_SONG_BUTTON, INPUT_PULLUP);

    attachInterrupt(PAUSE_PLAY_BUTTON, pausePlayButtonPressed, FALLING);
    attachInterrupt(NEXT_SONG_BUTTON, nextSongButtonPressed, FALLING);
    attachInterrupt(PREV_SONG_BUTTON, prevSongButtonPressed, FALLING);
}