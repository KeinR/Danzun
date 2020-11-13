#include "RealTimer.h"

dan::RealTimer::RealTimer(): RealTimer(0) {
}
dan::RealTimer::RealTimer(unsigned int ms): end(clock::now()) {
    setTime(ms);
}
void dan::RealTimer::setTime(unsigned int ms) {
    time = std::chrono::milliseconds(ms);
}
void dan::RealTimer::start() {
    end = clock::now() + time;
}
bool dan::RealTimer::done() {
    return clock::now() >= end;
}
