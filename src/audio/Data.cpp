#include "Data.h"

#include <cstring>
#include <fstream>
#include <stdexcept>

#include <stb/stb_vorbis.h>
#include <dr/dr_wav.h>

static dan::audio::Data doLoadVorbis(stb_vorbis *handle);
static dan::audio::Data doLoadWav(drwav *handle);

dan::audio::Data::Data(): dataBytes(0), frequency(0), format(0) {
}
dan::audio::Data::Data(const std::shared_ptr<data_t> &data, ALsizei dataBytes, ALsizei frequency, ALenum format):
    data(data), dataBytes(dataBytes), frequency(frequency), format(format) {
}

// Free data of a certain type.
// Apparently deleting a void pointer will cause undefined behavior...
// Was that just with objects? I dunno...
template<typename T>
static void freeData(const void *data) {
    delete[] (const T *)data;
}


dan::audio::Data doLoadVorbis(stb_vorbis *handle) {
    stb_vorbis_info info = stb_vorbis_get_info(handle);

    // The total stream length in samples is on a per-channel basis... The total length is that times the #channels
    const unsigned int bufferLength = stb_vorbis_stream_length_in_samples(handle) * info.channels;
    // stb_vorbis deals with only floats and shorts... And guess which one is closest to chars?
    short *data = new short[bufferLength];

    // This function just decodes data
	stb_vorbis_get_samples_short_interleaved(handle, info.channels, data, bufferLength);

    dan::audio::Data sd(
        std::shared_ptr<dan::audio::Data::data_t>(data, freeData<short>),
        bufferLength*sizeof(short),
        info.sample_rate,
        dan::audio::getALFormat(info.channels, 16)
    );

    stb_vorbis_close(handle);

    return sd;
}

dan::audio::Data doLoadWav(drwav *handle) {
    unsigned int sizeInBytes = handle->totalPCMFrameCount * handle->channels * sizeof(short);
    short *data = new short[sizeInBytes / sizeof(short)];

	drwav_read_pcm_frames_s16(handle, handle->totalPCMFrameCount, data);

    dan::audio::Data sd(
        std::shared_ptr<dan::audio::Data::data_t>(data, freeData<short>),
        sizeInBytes,
        handle->fmt.sampleRate,
        dan::audio::getALFormat(handle->fmt.channels, handle->fmt.bitsPerSample)
    );

    drwav_uninit(handle);

    return sd;
}


ALenum dan::audio::getALFormat(int channels, int bitsPerSample) {
    if (bitsPerSample == 8) {
        return channels > 1 ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
    } else {
        return channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
    }
    return 0;
}

dan::audio::Data dan::audio::loadWavFile(const std::string &path) {
    drwav wav;
    if (!drwav_init_file(&wav, path.c_str(), NULL)) {
        throw std::runtime_error("failed to decode");
    }
    return doLoadWav(&wav);
}
dan::audio::Data dan::audio::loadWavMemory(const unsigned char *data, int length) {
    drwav wav;
    if (!drwav_init_memory(&wav, data, length, NULL)) {
        throw std::runtime_error("failed to decode");
    }
    return doLoadWav(&wav);
}
dan::audio::Data dan::audio::loadVorbisFile(const std::string &path) {
    int error = 0;
    // The last parameter is the alloc buffer, which I don't really want to deal with
    stb_vorbis *handle = stb_vorbis_open_filename(path.c_str(), &error, NULL);
    if (error) {
        throw std::runtime_error("stb_vorbis_open_filename failed");
    }
    return doLoadVorbis(handle);
}
dan::audio::Data dan::audio::loadVorbisMemory(const unsigned char *data, int length) {
    int error = 0;
    stb_vorbis *handle = stb_vorbis_open_memory(data, length, &error, NULL);
    if (error) {
        throw std::runtime_error("stb_vorbis_open_memory failed");
    }
    return doLoadVorbis(handle);
}
