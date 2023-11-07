#include <Arduino.h>
#include "music.h"
#include "songs.h"
#include "controller.h"
#define MINUTE_MS 60 * 1000
#define BEATS_IN_WHOLE_NOTE 4

/*
  This file is a modified version of Robson Couto's code to play songs through an Arduino Buzzer.
  In his code, he has one song per .ino file, whereas I've modified the code into a module that
  can load any song in Couto's format into memory and play it.

  Robson Couto's code can be found here:
  https://github.com/robsoncouto/arduino-songs
*/

static bool songLoaded = false;
static int currentlyPlayingSongIndex = -1;

// Tracks the progress of the song across pause/play activity
static int currentNote = 0;

// Tracks the tempo of the song in beats per minute
static int tempo = 0;

// Tracks the number of notes in the song
static int numNotes = 0;

// the duration of a whole note in ms
static int wholenote = 0;

static const int* melody;

/*
  Selects a song from the songs array to be played
*/
void loadSongAtIndex(int index) {
  // prevents unnecessary loading of the same song & preserves currentNote
  // TODO: If we end up implementing a repeat feature, this might not be the 
  // best way to implement the behavior described above
  if(index == currentlyPlayingSongIndex) {
    return;
  }

  struct Song* song = getSongs()[index];

  tempo = song->tempo;

  // melody in Couto's format is stored like: [note, duration, note, duration]
  // so the number of notes is the length of the melody / 2
  numNotes = song->length / 2;

  
  // this calculates the duration of a whole note in ms
  wholenote = (MINUTE_MS * BEATS_IN_WHOLE_NOTE) / tempo;
  melody = song->melody;

  // start the song from the beginning
  currentNote = 0;
  currentlyPlayingSongIndex = index;
  songLoaded = true;
}

/*
  Plays the currently loaded song

  speaker_pin: the pin connected to the speaker on which the song will be played
*/
void playMusic(uint8_t speaker_pin) {
  if(!songLoaded) {
    // TODO: throw some error here
    return;
  }

  int divider = 0;
  int noteDuration = 0;

  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = currentNote; thisNote < numNotes * 2; thisNote = thisNote + 2) {
    // keep track of the current note for resuming after pause
    currentNote = thisNote;

    // we break out of the song if a pause or song change happens
    if(getIsPaused() || currentlyPlayingSongIndex != getCurrentSongIndex()) {
      break;
    }

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations
      noteDuration = (wholenote) / abs(divider);
      // increases the duration in half for dotted notes
      noteDuration *= 1.5; 
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(speaker_pin, melody[thisNote], noteDuration*0.9);

    // Wait for the specified duration before playing the next note
    delay(noteDuration);
    
    // stop the waveform generation before the next note
    noTone(speaker_pin);
  }
}