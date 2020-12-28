#include "Music.h"

#include <exception>
#include <stdexcept>

#include "../core/error.h"
#include "../audio/signature.h"
#include "SpeakerConf.h"

dan::api::Music::Music(sol::this_state l, const std::string &path) {
    failed = true;

    dan::audio::type t = dan::audio::getType(path);
    try {
        switch (t) {
            case dan::audio::type::WAV:
                stream = std::make_shared<dan::audio::WavStream>(path);
                break;
            case dan::audio::type::OGG:
                stream = std::make_shared<dan::audio::VorbisStream>(path);
                break;
            case dan::audio::type::NONE: // Fallthrough
            default:
                throw std::runtime_error("Unrecognized format");
                break;
        }
        failed = false;
    } catch (std::exception &e) {
        err("api::Music::Music", l) << "Failed to load sound effect \"" << path << "\": " << e.what();
    }
}

bool dan::api::Music::isFailed() {
    return failed;
}

void dan::api::Music::play(SpeakerConf *speaker) {
    speaker->getSpeaker().playStream(stream);
}
