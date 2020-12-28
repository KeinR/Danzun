#ifndef DANZUN_AUDIO_SIGNATURE_H_INCLUDED
#define DANZUN_AUDIO_SIGNATURE_H_INCLUDED

#include <string>

namespace dan::audio {
    enum class type {
        OGG,
        WAV,
        NONE
    };

    // There are ways to optimize this, ie not opening
    // the file twice
    type getType(const std::string &path);

}

#endif
