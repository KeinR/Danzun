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
    /**
     * A loaded sound (OGG or wav) as opposed to streamed.
     * That is, the entire decoded file is loaded into memory
     * */
    class SoundEffect: public Sound {
        /// The audio buffer
        std::shared_ptr<audio::Buffer> buffer;
        /// If the sound failed to load
        bool failed;
    public:
        /**
         * Construct with sound
         * \param l The current lua state
         * \param path Path to a valid sound file
         * */
        SoundEffect(sol::this_state l, const std::string &path);

        /**
         * Initializes the speaker with the buffer.
         * Required before play() can be called
         * \param speaker The parent speaker
         * */
        void initSpeaker(SpeakerConf *speaker);

        bool isFailed() override;
        void play(SpeakerConf *speaker) override;
    };
}

#endif
