#include "Event.h"

#include "../core/debug.h"

dan::Event::Event(Clock &c): timer(c) {
}
dan::Event::Event(Clock &ck, float s, const callback_t &c, bool autoStart):
    Event(ck)
{
    setTime(s);
    setTask(c);
    if (autoStart) {
        start();
    }
}
void dan::Event::setTask(const callback_t &c) {
    callback = c;
}
void dan::Event::setTime(float s) {
    timer.set(s);
}
void dan::Event::start() {
    timer.reset();
}
void dan::Event::poll() {
    DANZUN_ASSERT(callback);

    if (timer.done()) {
        callback(*this);
        timer.reset();
    }
}
