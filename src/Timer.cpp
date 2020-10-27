#include "Timer.h"

dan::Timer::Timer(): Timer(0) {
}
dan::Timer::Timer(unsigned int ms): paused(false), end(clock::now()) {
    setTime(ms);
}
void dan::Timer::setTime(unsigned int ms) {
    time = std::chrono::milliseconds(ms);
}
void dan::Timer::start() {
    end = clock::now() + time;
}
bool dan::Timer::done() {
    return clock::now() >= end && !paused;
}
