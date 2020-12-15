#include "Clock.h"

dan::Clock::Clock():
    time(0),
    deltaTime(0) {
}
void dan::Clock::setTime(float s) {
    time = s;
}
void dan::Clock::setDeltaTime(float s) {
    deltaTime = s;
}
void dan::Clock::pushDeltaTime(float s) {
    time += deltaTime;
    deltaTime = s;
}
float &dan::Clock::getTimeRef() {
    return time;
}
float &dan::Clock::getDeltaTimeRef() {
    return deltaTime;
}
float dan::Clock::getTime() const {
    return time;
}
float dan::Clock::getDeltaTime() const {
    return deltaTime;
}
