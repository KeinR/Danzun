#include "Device.h"

dan::audio::Device::Device(const ALCchar *devicename): handle(alcOpenDevice(devicename)) {
}

dan::audio::Device::~Device() {
    close();
}

void dan::audio::Device::close() {
    if (handle != nullptr) {
        alcCloseDevice(handle);
    }
}

void dan::audio::Device::steal(Device &other) {
    handle = other.handle;
    other.handle = nullptr;
}

void dan::audio::Device::copy(const Device &other) {
    handle = alcOpenDevice(alcGetString(other.handle, ALC_DEVICE_SPECIFIER));
}

dan::audio::Device::Device(Device &&other) {
    steal(other);
}
dan::audio::Device::Device(const Device &other) {
    copy(other);
}
dan::audio::Device &dan::audio::Device::operator=(Device &&other) {
    close();
    steal(other);
    return *this;
}
dan::audio::Device &dan::audio::Device::operator=(const Device &other) {
    close();
    copy(other);
    return *this;
}

ALCdevice *dan::audio::Device::get() const {
    return handle;
}
