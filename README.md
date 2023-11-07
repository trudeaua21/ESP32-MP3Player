# ESP32-MusicPlayer
An music player coded on the ESP32 microcontroller. Plays a playlist of songs through a piezoelectric buzzer, which has basic pause, play, next song, and previous song functionality implemented through switches.

## Building the Project
This project was built using [PlatformIO](https://platformio.org/). Build using either of the following options:

1. Install and set up [PlatformIO IDE extension for VSCode](https://platformio.org/install/ide?install=vscode)
2. Install [PlatformIO CLI](https://docs.platformio.org/en/latest/core/installation/index.html) and run the following command:
```
pio run
```

## Running the Project
Either flash the binary/elf files to a compatible ESP32 chip, or run the attached Wokwi simulator file. To run the simulator file, take the following steps:

1. Install [Wokwi for VSCode](https://docs.wokwi.com/vscode/getting-started)
2. In VSCode, press `F1`, run the command "Wowki: Select Config File" and select the project's `wokwi.toml` file
3. In VSCode, press `F1` and run the command "Wowki: Start Simulator"

## Song Credit
The code for playing the music (not including the pause/playlist features) and the files for the songs themselves are taken from https://github.com/robsoncouto/arduino-songs
