#include "pmeta.h"

static std::thread::id mainThread = std::this_thread::get_id();

std::thread::id dan::pmeta::getMainThreadId() {
    return mainThread;
}
bool dan::pmeta::onMainThread() {
    return std::this_thread::get_id() == getMainThreadId();
}
