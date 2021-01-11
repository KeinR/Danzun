#ifndef DANZUN_API_SPEAKERCONF_H_INCLUDED
#define DANZUN_API_SPEAKERCONF_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

#include "../audio/Speaker.h"
#include "Sound.h"

namespace dan::api {
    /**
     * A driver class that plays a sound
     * */
    class SpeakerConf {
        /// The speaker object (sound properties)
        std::shared_ptr<audio::Speaker> speaker;
        /// The sound to play
        std::shared_ptr<Sound> sound;
    public:
        /***
         * Construct with a sound (DO NOT CALL, use factories!)
         * \param sound The sound
         * */
        SpeakerConf(const std::shared_ptr<Sound> &sound);

        /**
         * Creates a streamed sound
         * \param l The current state
         * \param path The path to the sound
         * \return The new speaker
         * */
        static SpeakerConf makeStream(sol::this_state l, const std::string &path);
        /**
         * Creates a loaded sound
         * \param l The current state
         * \param path The path to the sound
         * \return The new speaker
         * */
        static SpeakerConf makeEffect(sol::this_state l, const std::string &path);

        /**
         * \return The speakre handle
         * */
        audio::Speaker &getSpeaker();

        /**
         * \return the fail state if the sound
         * */
        bool isFailed();
        /**
         * Play the sound
         * \param l The current state
         * */
        void play(sol::this_state l);

        /**
         * Registers this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view lua);
    };
}

#endif
