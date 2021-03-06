#include "Timer.h"

Timer::Timer(timer_callback_t callback, uint8_t value):
  ticks(0),
  target_ticks(value),
  last_ticks(0),
  callback(callback)
{}


void Timer::tick(uint8_t elapsed) {
  ticks += elapsed-last_ticks;
  last_ticks = elapsed;

  if (ticks >= target_ticks) {
    callback(ticks-target_ticks);
    reset();
  }
}


uint8_t Timer::get_count() {
  return ticks;
}


void Timer::reset() {
  ticks = 0;
}
