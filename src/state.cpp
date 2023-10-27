#include "state.h"
#define DEBOUNCE_TIME_MS 250


bool is_paused = false;

//variables to keep track of the timing of recent interrupts
static unsigned long button_time = 0;  
static unsigned long last_pressed_time = 0; 

void IRAM_ATTR pause_play_button_pressed() {
    button_time = millis();

    // TODO: might be a problem once millis() overflows?
    if(button_time - last_pressed_time > DEBOUNCE_TIME_MS) {
        is_paused = !is_paused;
        last_pressed_time = button_time;
    }
}