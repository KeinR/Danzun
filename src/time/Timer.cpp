#include "Timer.h"

dan::Timer::Timer(): Timer(0) {
}
dan::Timer::Timer(unsigned int ms): end(clock::now()) {
    setTime(ms);
}
void dan::Timer::setTime(unsigned int ms) {
    time = std::chrono::milliseconds(ms);
}
unsigned int dan::Timer::getTime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
}
void dan::Timer::start() {
    end = clock::now() + time;
}
bool dan::Timer::done() {
    return clock::now() >= end;
}
