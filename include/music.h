#ifndef MUSIC_H
#define MUSIC_H

#include <Arduino.h>

extern void loadSongAtIndex(int index);
extern void playMusic(uint8_t speaker_pin);

#endif