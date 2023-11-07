#include "controller.h"
#include "songs.h"
#define DEBOUNCE_TIME_MS 250

// TODO: get rid of bool usage so I'm only using C features
static volatile bool isPaused = false;

// can underflow if the prev button is pressed on index - handled in accessor
static volatile int currentSongIndex = 0;

//variables to keep track of the timing of recent interrupts
static unsigned long playButtonTime = 0;
static unsigned long playButtonLastPressedTime = 0;

static unsigned long nextSongButtonTime = 0;
static unsigned long nextSongButtonLastPressedTime = 0;

static unsigned long prevSongButtonTime = 0;
static unsigned long prevSongButtonLastPressedTime = 0;


bool getIsPaused() {
    bool temp;

    // TODO: retool this to preserve interrupts on/off state from before the call
    noInterrupts();
    temp = isPaused;
    interrupts();
    return temp;
}

/*
To speed up the interrupts, boundary checking against number of songs is handled here
*/
int getCurrentSongIndex() {
    int temp;

    // TODO: retool this to preserve interrupts on/off state from before the call
    noInterrupts();
    if(currentSongIndex < 0) {
        currentSongIndex = getNumSongs() - 1;
    } else if(currentSongIndex >= getNumSongs()) {
        currentSongIndex = 0;
    }

    temp = currentSongIndex;
    interrupts();
    return temp;
}

void IRAM_ATTR pausePlayButtonPressed() {
    // TODO: retool this to be impervious to millis() overflow
    playButtonTime = millis(); 

    if(playButtonTime - playButtonLastPressedTime > DEBOUNCE_TIME_MS) {
        isPaused = !isPaused;
        playButtonLastPressedTime = playButtonTime;
    }
}

void IRAM_ATTR nextSongButtonPressed() {
    nextSongButtonTime = millis();

    if(nextSongButtonTime - nextSongButtonLastPressedTime > DEBOUNCE_TIME_MS) {
        currentSongIndex++;
        // even if we're paused, we want to play the new song after switch
        isPaused = false;

        nextSongButtonLastPressedTime = nextSongButtonTime;
    }
}

void IRAM_ATTR prevSongButtonPressed() {
    prevSongButtonTime = millis();

    if(prevSongButtonTime - prevSongButtonLastPressedTime > DEBOUNCE_TIME_MS) {
        currentSongIndex--;
        // even if we're paused, we want to play the new song after switch
        isPaused = false;

        prevSongButtonLastPressedTime = prevSongButtonTime;
    }
}