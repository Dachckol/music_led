#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef void (*timer_callback_t)(uint8_t);


class Timer {
public:
  Timer(timer_callback_t callback, uint8_t value);
  void tick(uint8_t elapsed);
  uint8_t get_count();
  void reset();
private:
  uint8_t ticks;
  uint8_t target_ticks;

  timer_callback_t callback;

};

#endif
