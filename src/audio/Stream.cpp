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

// Check if string is equal as it's being read
// is this more efficient than reading and then comparing?
// `cstr` is the expected string
// `file` is the stream
// `err` is the error message should the stream data and `cstr` not match
static void strEq(std::ifstream &file, const char *cstr, const char *err) {
    // Read for length of given expected string, `cstr`
    for (int ci = 0; cstr[ci]; ci++) {
        if (file.eof()) {
            throw std::runtime_error("Corrupted");
        }
        if (file.get() != cstr[ci]) {
            throw std::runtime_error(err);
        }
    }
}

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
void dan::audio::WavStream::open(const std::string &file) {
    stream.open(file);
    if (!stream.good()) {
        throw std::runtime_error("Failed to open stream");
    }

    // Parse PCM wav header
    // http://www.topherlee.com/software/pcm-tut-wavformat.html
    // https://stackoverflow.com/a/13059080/10821333

    strEq(stream, "RIFF", "Corrupted"); // Check has RIFF header

    stream.ignore(4); // Total file size. This value is kinda' useless
    strEq(stream, "WAVEfmt ", "Not PCM WAV 1"); // Check has "WAVEfmt ", signifies correct format
    if (readInt(stream) != 16) {
        throw std::runtime_error("Corrupted");
    }
    if (readShort(stream) != 1) { // Flag that tells if PCM
        throw std::runtime_error("Not PCM WAV");
    }
    const int channels = readShort(stream); // So from what I understand, it's one sample per channel
    info.frequency = readInt(stream); // aka sample rate, samples per second
    info.bytesPerSecond = readInt(stream); // How many _bytes_ are read per second
    info.blockAlign = readShort(stream); // Min. bytes per block. Need to truncate to mod of this else OpenAL freaks out and dies
    const short bits_per_sample = readShort(stream); // aka "samples", aka "sample size"
    // After this point, there can be a buch of junk data. Luckily, we can just seek
    // to the end of that chunk, the "data" header
    for (int f = 0; f < 4;) {
        if (stream.eof()) {
            throw std::runtime_error("Corrupted, header truncated");
        }
        if ("data"[f] == stream.get()) {
            f++;
        }
    }
    // Unlike the previous length, this length is actually useful, for it tells the
    // length of the following data. Obviously, we'll only use this as a guideline, for
    // we don't know if the file was truncated or not... Well we could check with tellg, but
    // there's no need
    const streampos_t declaredLength = readInt(stream);

    if (!stream.good()) {
        throw std::runtime_error("Failed to read header");
    }

    // Keep track of these offsets so that we can seek properly
    start = stream.tellg();
    end = start + declaredLength;

    info.format = getALFormat(channels, bits_per_sample);
}

const dan::audio::soundInfo &dan::audio::WavStream::getInfo() {
    return info;
}

bool dan::audio::WavStream::read(char *buffer, streampos_t &length) {
    bool done = false;
    if (stream.tellg() + length >= end) {
        length = end - stream.tellg();
        length -= length % info.blockAlign;
        if (length <= 0) {
            length = 0;
            return true;
        }
        done = true;
    }
    stream.read(buffer, length);
    if (stream.eof()) {
        // Failsafe, clear errors and reduce length to account for truncation
        stream.clear();
        length -= length - stream.tellg();
        length -= length % info.blockAlign;
        done = true;
    } else if (!stream.good()) {
        throw std::runtime_error("Stream read failed");
    }
    return done;
}
void dan::audio::WavStream::seek(float seconds) {
    streampos_t s = std::floor(info.bytesPerSecond * seconds);
    s -= s % info.blockAlign;
    stream.seekg(s);
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
    // stb_vorbis seeks by samples as opposed to bytes with our WAV
    streampos_t s = std::floor(vInfo.sample_rate * vInfo.channels * seconds);
    s -= s % info.blockAlign;
    stb_vorbis_seek(decoder, s);
}
