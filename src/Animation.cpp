#include "Animation.h"

#include "core/debug.h"

static void defaultCallback(dan::Animation::Instance &inst) {
    inst.restart();
}

dan::Animation::Instance::Instance():
    parent(nullptr),
    timeToFlip(0),
    index(0) {
}

dan::Animation::Instance::Instance(Animation &parent):
    parent(&parent),
    timeToFlip(0),
    index(0)
{
    restart();
}
void dan::Animation::Instance::restart() {
    DANZUN_ASSERT(parent != nullptr);

    index = 0;
    timeToFlip = parent->getFrame(0).getLength();
}
void dan::Animation::Instance::advance(float deltaTime) {
    DANZUN_ASSERT(parent != nullptr);

    timeToFlip -= deltaTime;
    if (timeToFlip <= 0) {
        index++;
        if (index < parent->countFrames()) {
            timeToFlip = parent->getFrame(index).getLength();
        } else {
            index = 0; // For safety
            parent->callCallback(*this);
        }
    }
}

void dan::Animation::Instance::setup(Context &c) {
    DANZUN_ASSERT(parent != nullptr);

    parent->getFrame(index).setup(c);
}

void dan::Animation::Instance::render(Context &c) {
    DANZUN_ASSERT(parent != nullptr);

    parent->getFrame(index).render(c);
}

dan::Animation::Animation(): callback(defaultCallback) {
}

dan::Animation::Instance dan::Animation::newInstance() {
    return Instance(*this);
}

void dan::Animation::setCallback(const callback_t &func) {
    DANZUN_ASSERT(func);
    callback = func;
}

void dan::Animation::callCallback(Instance &inst) {
    callback(inst);
}

void dan::Animation::pushFrame(const Frame &frame) {
    frames.push_back(frame);
}
dan::Frame &dan::Animation::getFrame(unsigned int index) {
    DANZUN_ASSERT(index < frames.size());
    return frames[index];
}
unsigned int dan::Animation::countFrames() {
    return frames.size();
}
