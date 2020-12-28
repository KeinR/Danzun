#ifndef DANZUN_API_SOUND_H_INCLUDED
#define DANZUN_API_SOUND_H_INCLUDED

namespace dan::api {
    class SpeakerConf;
}

namespace dan::api {
    class Sound {
    public:
        virtual ~Sound() = 0;
        virtual bool isFailed() = 0;
        virtual void play(SpeakerConf *speaker) = 0;
    };
}

#endif
