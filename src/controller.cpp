#include "controller.h"
#include "songs.h"
#define DEBOUNCE_TIME_MS 250

/*  
    NOTE: this is both the controller and model, which is necessary for
    the faster function of the interrupts (if the model data was encapsulated in another module,
    the interrupts would have to call the accessors for that data instead of getting it directly)
*/

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


/*
    Accessor for pause state    
*/
bool getIsPaused() {
    bool temp;

    // TODO: retool this to preserve interrupts on/off state from before the call
    noInterrupts();
    temp = isPaused;
    interrupts();
    return temp;
}

/*
    Accessor for current song index
    To prevent doing so in the time-sensitive interrupts, this accessor checks if
    the song index is out of bounds, and over/underflows it to the appropriate song
    if the index is < 0 or > number of songs
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

/*
    Debounced interrupt handler for the pause/play switch
*/
void IRAM_ATTR pausePlayButtonPressed() {
    playButtonTime = millis(); 

    if(playButtonTime - playButtonLastPressedTime > DEBOUNCE_TIME_MS) {
        isPaused = !isPaused;
        playButtonLastPressedTime = playButtonTime;
    }
}

/*
    Debounced interrupt handler for the next song button
*/
void IRAM_ATTR nextSongButtonPressed() {
    nextSongButtonTime = millis();

    if(nextSongButtonTime - nextSongButtonLastPressedTime > DEBOUNCE_TIME_MS) {
        currentSongIndex++;
        // even if we're paused, we want to play the new song after switch
        isPaused = false;

        nextSongButtonLastPressedTime = nextSongButtonTime;
    }
}


/*
    Debounced interrupt handler for the previous song button
*/
void IRAM_ATTR prevSongButtonPressed() {
    prevSongButtonTime = millis();

    if(prevSongButtonTime - prevSongButtonLastPressedTime > DEBOUNCE_TIME_MS) {
        currentSongIndex--;
        // even if we're paused, we want to play the new song after switch
        isPaused = false;

        prevSongButtonLastPressedTime = prevSongButtonTime;
    }
}