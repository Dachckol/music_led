#include <Arduino.h>
#include <arduinoFFT.h>
#include <stdint.h>


#include "Timer.h"
#include "LEDCalculator.h"

#define SAMPLE_RATE 16000 // Arduino is 16 MHz giving 1000 cycles per sample
#define FRAME_SIZE 128 // must be a power of 2 for FFT algorithm
#define BINS 3



double buffer[FRAME_SIZE];
uint8_t current_index;


Timer *timer;
LEDCalculator* led_calculator;
arduinoFFT* fft;


// callback for Timer - synchronous
void save_sample(uint8_t excess) {
  if (current_index < FRAME_SIZE) {
    float sound_value = (float)(analogRead(A0)-500)/1000;
    buffer[current_index++] = sound_value;
  }
}


void process_buffer() {
  // buffer processing is done in-place, but we need another one for the imaginary values
  double buffer_img[FRAME_SIZE] = {0};

  fft->Windowing(buffer, FRAME_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  fft->Compute(buffer, buffer_img, FRAME_SIZE, FFT_FORWARD);
  fft->ComplexToMagnitude(buffer, buffer_img, FRAME_SIZE);

  led_calculator->calculate(buffer, FRAME_SIZE/2);

  analogWrite(A1, led_calculator->get_red());
  analogWrite(A2, led_calculator->get_green());
  analogWrite(A3, led_calculator->get_blue());
}


void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  current_index = 0;

  // RAM will be flashed on reset so no need to tear these down
  timer = new Timer(&save_sample, 1000000/SAMPLE_RATE);
  led_calculator = new LEDCalculator(13000);
  fft = new arduinoFFT();
}


void loop() {
  // Will call save_sample when at target delay
  timer->tick(micros());

  if (current_index >= FRAME_SIZE) {
    current_index = 0;
    process_buffer();
  }
}


