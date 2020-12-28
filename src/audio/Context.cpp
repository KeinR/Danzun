#include "Context.h"

#include <iostream> // DEBUG
#include <cstddef>

dan::audio::Context::Context(const Device &device):
    // Create context without an attribute list in the given device...
    // Dont' know how to make one though, the docs are kinda' vague...
    handle(alcCreateContext(device.get(), NULL))
{}

dan::audio::Context::~Context() {
    close();
}

void dan::audio::Context::close() {
    if (handle != nullptr) {
        // Set context to null if this one is in use...
        // It'll make debugging easier, and prevent seg faults
        if (alcGetCurrentContext() == handle) {
            alcMakeContextCurrent(NULL);
        }
        alcDestroyContext(handle);
    }
}

void dan::audio::Context::steal(Context &other) {
    handle = other.handle;
    other.handle = nullptr;
}
void dan::audio::Context::copy(const Context &other) {
    // Kinda' a hack, but worth it I think to get copy semantics
    // Won't copy over bindings, etc. of course
    handle = alcCreateContext(alcGetContextsDevice(other.handle), NULL);
}

dan::audio::Context::Context(Context &&other) {
    steal(other);
}
dan::audio::Context::Context(const Context &other) {
    copy(other);
}
dan::audio::Context &dan::audio::Context::operator=(Context &&other) {
    // Close because it's already been constructed with a device
    close();
    steal(other);
    return *this;
}
dan::audio::Context &dan::audio::Context::operator=(const Context &other) {
    close();
    copy(other);
    return *this;
}

bool dan::audio::Context::bind() const {
    return alcMakeContextCurrent(handle);
}
