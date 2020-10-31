#include "Timer.h"

dan::Timer::Timer() {
    set(0);
    reset();
}
void dan::Timer::advance(float s) {
    progress += s;
}
void dan::Timer::set(float duration) {
    goal = duration;
}
void dan::Timer::reset() {
    progress = 0;
}
bool dan::Timer::done() const {
    return progress >= goal;
}
