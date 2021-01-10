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
    /**
     * Streamed sound (ogg or WAV)
     * */
    class Music: public Sound {
        /// Handle to the stream
        std::shared_ptr<audio::Stream> stream;
        /// If the stream failed to load or is invalid
        bool failed;
    public:
        /**
         * Construct a music stream (USE \ref make)
         * \param l The current state
         * \param path Path to the sound file
         * */
        Music(sol::this_state l, const std::string &path);

        /**
         * Create a new stream
         * \param l The current state
         * \param path Path to the sound file
         * \return The new sound
         * */
        SpeakerConf make(sol::this_state l, const std::string &path);

        bool isFailed() override;
        void play(SpeakerConf *speaker) override;
    };
}

#endif
