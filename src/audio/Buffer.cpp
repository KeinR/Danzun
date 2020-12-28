#include "Buffer.h"

dan::audio::Buffer::Buffer(const Data &data):
    Buffer(data.data.get(), data.dataBytes, data.frequency, data.format) {
}
dan::audio::Buffer::Buffer(const void *data, ALsizei dataBytes, ALsizei frequency, ALenum format) {
    alGenBuffers(1, &buffer);
	alBufferData(buffer, format, data, dataBytes, frequency);
}
dan::audio::Buffer::~Buffer() {
    close();
}
void dan::audio::Buffer::close() {
    if (buffer) {
        alDeleteBuffers(1, &buffer);
    }
}
void dan::audio::Buffer::steal(Buffer &other) {
    buffer = other.buffer;
    other.buffer = 0;
}

dan::audio::Buffer::Buffer(Buffer &&other) {
    steal(other);
}
dan::audio::Buffer &dan::audio::Buffer::operator=(Buffer &&other) {
    close();
    steal(other);
    return *this;
}

ALuint dan::audio::Buffer::get() const {
    return buffer;
}
