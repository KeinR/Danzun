#ifndef DANZUN_AUDIO_BUFFER_H_INCLUDED
#define DANZUN_AUDIO_BUFFER_H_INCLUDED

#include "../lib/audio.h"

#include "Data.h"

/*
* Buffers are specific to a given device.
* They are independent of contexts.
* https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf#page=8
* Note: OpenAL buffers copy the data given to them, so you can, and should, free the data afterwards.
*/

namespace dan::audio {
    class Buffer {
        ALuint buffer;
        void close();
        void steal(Buffer &other);
    public:
        // From a Data object
        Buffer(const Data &data);
        // From meta and actual data
        Buffer(const void *data, ALsizei dataBytes, ALsizei frequency, ALenum format);
        // From what the docs have said, it appears to be impossible to read data from a OpenAL
        // sound buffer. You can get a pointer to the source data that was given to it, but
        // there's not garuntee that it's not been free'd/delete'd. Ergo, copying is prevented.
        Buffer(Buffer &&other);
        ~Buffer();
        Buffer &operator=(Buffer &&other);

        // Gets the wrapped OpenAL buffer
        ALuint get() const;
    };
};

#endif
