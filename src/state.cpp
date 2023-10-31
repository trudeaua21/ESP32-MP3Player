#include "state.h"
#define DEBOUNCE_TIME_MS 250

// TODO: get rid of bool usage so I'm only using C features
static volatile bool isPaused = false;

//variables to keep track of the timing of recent interrupts
static unsigned long button_time = 0;
static unsigned long last_pressed_time = 0;


bool getIsPaused() {
    bool temp;

    // TODO: retool this to preserve interrupts on/off state from before the call
    noInterrupts();
    temp = isPaused;
    interrupts();
    return temp;
}

void IRAM_ATTR pausePlayButtonPressed() {
    // TODO: retool this to be impervious to millis() overflow
    button_time = millis(); 

    if(button_time - last_pressed_time > DEBOUNCE_TIME_MS) {
        isPaused = !isPaused;
        last_pressed_time = button_time;
    }
}