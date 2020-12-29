#include "Stream.h"


#include <cmath>
#include <stdexcept>

#include "Data.h"

// Read a little endian number from a stream
// templated for short and int
template<typename T>
static T readNumber(std::ifstream &file) {
    // The end will be the bit size of the number, minus 8
    constexpr int end = (sizeof(T) / sizeof(char) - 1) * 8;
    T result = 0;
    for (int s = 0; s <= end; s += 8) {
        if (file.eof()) {
            throw std::runtime_error("Corrupted");
        }
        result |= file.get() << s;
    }
    return result;
}

// Alias templates
auto constexpr readInt = &readNumber<int>;
auto constexpr readShort = &readNumber<short>;

dan::audio::Stream::Stream(): locked(false) {
}
dan::audio::Stream::~Stream() {
}

bool dan::audio::Stream::inUse() {
    return locked;
}
bool dan::audio::Stream::lock() {
    if (locked) {
        return true;
    }
    locked = true;
    return false;
}
void dan::audio::Stream::release() {
    locked = false;
}

dan::audio::WavStream::WavStream(const std::string &file) {
    open(file);
}
dan::audio::WavStream::~WavStream() {
    drwav_uninit(&wav);
}
void dan::audio::WavStream::open(const std::string &file) {
    drwav wav;
    if (!drwav_init_file(&wav, file.c_str(), NULL)) {
        throw std::runtime_error("Failed to decode");
    }

    info.frequency = wav.fmt.sampleRate;
    info.format = getALFormat(wav.fmt.channels, wav.fmt.bitsPerSample);
    info.bytesPerSecond = wav.fmt.avgBytesPerSec;
    info.blockAlign = wav.fmt.blockAlign;

    // Hey I'm kinda' liking these dr_ libs
}

const dan::audio::soundInfo &dan::audio::WavStream::getInfo() {
    return info;
}

bool dan::audio::WavStream::read(char *buffer, streampos_t &length) {
    length -= length % wav.fmt.blockAlign;
    drwav_uint64 len = length / wav.fmt.channels / sizeof(short);
    drwav_uint64 lenResult = drwav_read_pcm_frames_s16(&wav, len, reinterpret_cast<short*>(buffer));
    length = len * wav.fmt.channels * sizeof(short);
    return lenResult < len;
}
void dan::audio::WavStream::seek(float seconds) {
    // Should work but idunno man
    streampos_t s = std::floor(wav.fmt.sampleRate * wav.fmt.channels * seconds);
    s -= s % wav.fmt.blockAlign;
    drwav_seek_to_pcm_frame(&wav, s);
}





dan::audio::VorbisStream::VorbisStream(const std::string &file): Stream() {
    int error = 0;
    decoder = stb_vorbis_open_filename(file.c_str(), &error, NULL);
    if (error) {
        throw std::runtime_error("Failed to decode");
    }
    // I can't actually figure out how to get the bits per sample from stb_vorbis,
    // so I assume that it's 16...
    constexpr int vorbisBitsPerSample = 16;
    vInfo = stb_vorbis_get_info(decoder);
    info.frequency = vInfo.sample_rate;
    info.format = getALFormat(vInfo.channels, vorbisBitsPerSample);
    // sample/second * bytes/sample * channels
    // 1/second * bytes/1 * channels
    // bytes/second * channels
    // The channels act as a sort of a multiplier
    info.bytesPerSecond = vInfo.sample_rate * vorbisBitsPerSample * vInfo.channels / 8;
    // Each "unit" of sound, the sample size * channels
    info.blockAlign = vorbisBitsPerSample * vInfo.channels / 8;
}

dan::audio::VorbisStream::~VorbisStream() {
    if (decoder != nullptr) {
        stb_vorbis_close(decoder);
    }
}
dan::audio::VorbisStream::VorbisStream(VorbisStream &&other) {
    decoder = other.decoder;
    other.decoder = nullptr;
    vInfo = other.vInfo;
    info = other.info;
}

const dan::audio::soundInfo &dan::audio::VorbisStream::getInfo() {
    return info;
}
bool dan::audio::VorbisStream::read(char *buffer, streampos_t &length) {
    // We're going to have to halve it to get short length, so...
    length -= length % 2;
    // Returns number samples added to buffer. Times that by channels to get total samples, and multiply by 2 to get that it bytes
    // (because stb_vorbis samples are shorts)
    length = stb_vorbis_get_samples_short_interleaved(decoder, vInfo.channels, reinterpret_cast<short*>(buffer), length / 2) * vInfo.channels * 2;
    return length == 0;
}
void dan::audio::VorbisStream::seek(float seconds) {
    // stb_vorbis seeks by samples
    streampos_t s = std::floor(vInfo.sample_rate * vInfo.channels * seconds);
    s -= s % info.blockAlign;
    stb_vorbis_seek(decoder, s);
}
