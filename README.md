# Introduction

Platform IO project.

Requires arduinoFFT

Will take an analog audio input on A0 (taking 0 as value 500).

Realtime RGB output on A1, A2, A3 respectively.

## Building

Install platformio

### Update submodules

`git submodule update --recursive --init`

### Run build

`platformio run`

### Deploy to arduino

`platformio run --target upload`

# Result

Frequencies are divided into 3 bins based on frequency(`f`):

* f < 450Hz  - Bass (blue)
* 450 <= f < 2000 - Midrange (green)
* 2000 <= f - Upper range (red)

Based loosely on [this](https://www.teachmeaudio.com/mixing/techniques/audio-spectrum)
