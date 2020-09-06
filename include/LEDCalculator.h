#ifndef LED_CALCULATOR_H
#define LED_CALCULATOR_H

#include <stdint.h>

class LEDCalculator {
public:

  explicit LEDCalculator(uint16_t sample_rate);

  void calculate(double* buffer, uint8_t size);
  uint8_t get_red();
  uint8_t get_green();
  uint8_t get_blue();


private:

  void normalize(float& r, float& g, float& b);

  uint8_t red;
  uint8_t green;
  uint8_t blue;

  const uint16_t sample_rate;

  const float min_signal;

};


#endif // LED_CALCULATOR_H
