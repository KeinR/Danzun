#ifndef DANZUN_API_SPEAKERCONF_H_INCLUDED
#define DANZUN_API_SPEAKERCONF_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

#include "../audio/Speaker.h"
#include "Sound.h"

namespace dan::api {
    class SpeakerConf {
        std::shared_ptr<audio::Speaker> speaker;
        std::shared_ptr<Sound> sound;
    public:
        SpeakerConf(const std::shared_ptr<Sound> &sound);

        static SpeakerConf makeStream(sol::this_state l, const std::string &path);
        static SpeakerConf makeEffect(sol::this_state l, const std::string &path);

        audio::Speaker &getSpeaker();

        bool isFailed();
        void play(sol::this_state l);

        static void open(sol::state_view lua);
    };
}

#endif
