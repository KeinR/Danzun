#include "Timer.h"

#include "Clock.h"

dan::Timer::Timer(const Clock &clock): clock(&clock) {
    set(0);
    reset();
}
void dan::Timer::set(float s) {
    duration = s;
}
void dan::Timer::reset() {
    end = clock->getTime() + duration;
}
bool dan::Timer::done() const {
    return clock->getTime() >= end;
}
