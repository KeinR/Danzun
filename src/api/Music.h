#ifndef DANZUN_API_MUSIC_H_INCLUDED
#define DANZUN_API_MUSIC_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

#include "../audio/Stream.h"
#include "Sound.h"

namespace dan::api {
    class SpeakerConf;
}

namespace dan::api {
    class Music: public Sound {
        std::shared_ptr<audio::Stream> stream;
        bool failed;
    public:
        Music(sol::this_state l, const std::string &path);

        SpeakerConf make(sol::this_state l, const std::string &path);

        bool isFailed() override;
        void play(SpeakerConf *speaker) override;
    };
}

#endif
