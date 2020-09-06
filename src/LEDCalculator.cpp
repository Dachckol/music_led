#include "LEDCalculator.h"

#include <Arduino.h>
//#define DEBUG

#define max(a,b) ((a)>(b)?(a):(b))


LEDCalculator::LEDCalculator(int sample_rate):
  red{},
  green{},
  blue{},
  sample_rate{sample_rate},
  min_signal{0.01}
{
}


void LEDCalculator::calculate(double* buffer, uint8_t size) {
  blue = 0;
  green = 0;
  red = 0;
  float bins[3] = {0};
  for (int i = 2; i < size; i++) {
    if (buffer[i] < min_signal) continue;

    const int frequency = i*(float)sample_rate/(size << 1);
#ifdef DEBUG
    Serial.print(frequency);
    Serial.print("Hz = ");
    Serial.println(buffer[i]);
#endif

    if (frequency < 450) bins[0] += buffer[i] * 0.5;
    else if (frequency < 2000) bins[1] += buffer[i] * 2;
    else bins[2] += buffer[i] * 3;
  }

  float bluef = bins[0];
  float greenf = bins[1];
  float redf = bins[2];

  normalize(redf, greenf, bluef);

#ifdef DEBUG
    Serial.print("R");
    Serial.print(red);
    Serial.print(" G");
    Serial.print(green);
    Serial.print(" B");
    Serial.print(blue);
    Serial.println();
#endif

  red = (uint8_t)(redf*170);
  green = (uint8_t)(greenf*170);
  blue = (uint8_t)(bluef*170);
}


void LEDCalculator::normalize(float& r, float& g, float& b) {
  float maximum = max(r, max(g, b));
  r = r/maximum;
  g = g/maximum;
  b = b/maximum;
}


uint8_t LEDCalculator::get_red() {
  return red;
}


uint8_t LEDCalculator::get_green() {
  return green;
}


uint8_t LEDCalculator::get_blue() {
  return blue;
}


