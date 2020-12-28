#include "SoundEffect.h"

#include <exception>
#include <stdexcept>

#include "../core/error.h"
#include "../audio/signature.h"
#include "SpeakerConf.h"

dan::api::SoundEffect::SoundEffect(sol::this_state l, const std::string &path) {
    failed = true;

    dan::audio::type t = dan::audio::getType(path);
    try {
        audio::Data data;
        switch (t) {
            case dan::audio::type::WAV:
                data = dan::audio::loadWavFile(path);
                break;
            case dan::audio::type::OGG:
                data = dan::audio::loadVorbisFile(path);
                break;
            case dan::audio::type::NONE: // Fallthrough
            default:
                throw std::runtime_error("Unrecognized format");
                break;
        }
        buffer = std::make_shared<audio::Buffer>(data);
        failed = false;
    } catch (std::exception &e) {
        err("api::SoundEffect::SoundEffect", l) << "Failed to load sound effect \"" << path << "\": " << e.what();
    }
}

bool dan::api::SoundEffect::isFailed() {
    return failed;
}

void dan::api::SoundEffect::initSpeaker(SpeakerConf *speaker) {
    if (!failed) { // Just to be safe
        speaker->getSpeaker().setBuffer(buffer);
    }
}

void dan::api::SoundEffect::play(SpeakerConf *speaker) {
    speaker->getSpeaker().play();
}
