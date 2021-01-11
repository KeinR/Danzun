#ifndef DANZUN_API_SOUND_H_INCLUDED
#define DANZUN_API_SOUND_H_INCLUDED

namespace dan::api {
    class SpeakerConf;
}

namespace dan::api {
    /**
     * An abstract sound - can represent either a streamed or
     * loaded sound.
     * */
    class Sound {
    public:
        virtual ~Sound() = 0;
        /**
         * Returns true if the sound failed to load/initialize or is
         * otherwise invalid.
         * \return true if yes
         * */
        virtual bool isFailed() = 0;
        /**
         * Plays the sound asynchronously
         * \param speaker The host speaker
         * */
        virtual void play(SpeakerConf *speaker) = 0;
    };
}

#endif
