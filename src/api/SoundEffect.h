#ifndef DANZUN_API_SOUNDEFFECT_H_INCLUDED
#define DANZUN_API_SOUNDEFFECT_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

#include "../audio/Buffer.h"
#include "Sound.h"

namespace dan::api {
    class SpeakerConf;
}

namespace dan::api {
    class SoundEffect: public Sound {
        std::shared_ptr<audio::Buffer> buffer;
        bool failed;
    public:
        SoundEffect(sol::this_state l, const std::string &path);

        void initSpeaker(SpeakerConf *speaker);

        bool isFailed() override;
        void play(SpeakerConf *speaker) override;
    };
}

#endif
