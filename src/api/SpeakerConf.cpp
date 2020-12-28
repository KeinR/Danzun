#include "SpeakerConf.h"

#include "Music.h"
#include "SoundEffect.h"
#include "../game/Game.h"
#include "../core/error.h"

dan::api::SpeakerConf::SpeakerConf(const std::shared_ptr<Sound> &sound):
    speaker(std::make_shared<audio::Speaker>()), sound(sound) {
}

dan::api::SpeakerConf dan::api::SpeakerConf::makeStream(sol::this_state l, const std::string &path) {
    return SpeakerConf(std::make_shared<Music>(l, path));
}
dan::api::SpeakerConf dan::api::SpeakerConf::makeEffect(sol::this_state l, const std::string &path) {
    std::shared_ptr<SoundEffect> s = std::make_shared<SoundEffect>(l, path);
    SpeakerConf speaker(s);
    s->initSpeaker(&speaker);
    return speaker;
}

dan::audio::Speaker &dan::api::SpeakerConf::getSpeaker() {
    return *speaker;
}

bool dan::api::SpeakerConf::isFailed() {
    return sound->isFailed();
}

void dan::api::SpeakerConf::play(sol::this_state l) {
    Game::fromLua(l).addSpeaker(speaker);
    try {
        sound->play(this);
    } catch (std::exception &e) {
        // Is very unlikely
        err("api::SpeakerConf::play", l) << "[UNEXPECTED] Failed in playing sound: " << e.what();
    }
}

void dan::api::SpeakerConf::open(sol::state_view lua) {
    sol::usertype<SpeakerConf> type = lua.new_usertype<SpeakerConf>("Sound");

    type["openStream"] = &SpeakerConf::makeStream;
    type["loadFile"] = &SpeakerConf::makeEffect;
    type["play"] = &SpeakerConf::play;
    type["failed"] = sol::property(&SpeakerConf::isFailed);
}
