#include "Event.h"

#include "../core/debug.h"

template<class T>
dan::Event<T>::Event(const Clock &c): timer(c) {
}
template<class T>
dan::Event<T>::Event(const Clock &ck, float s, const callback_t &c, bool autoStart):
    Event(ck)
{
    setTime(s);
    setTask(c);
    if (autoStart) {
        start();
    }
}
template<class T>
void dan::Event<T>::setTask(const callback_t &c) {
    callback = c;
}
template<class T>
void dan::Event<T>::setTime(float s) {
    timer.set(s);
}
template<class T>
void dan::Event<T>::start() {
    timer.reset();
}
template<class T>
template<class... Args>
void dan::Event<T>::poll(Args&&... args) {
    DANZUN_ASSERT(callback);

    if (timer.done()) {
        callback(std::forward<Args>(args)...);
        timer.reset();
    }
}
