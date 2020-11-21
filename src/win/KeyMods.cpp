#include "KeyMods.h"

#include "enums.h"

dan::KeyMods::KeyMods(int mods): mods(mods) {
}
bool dan::KeyMods::shift() const {
    return (mods & (int)keyMod::SHIFT) == (int)keyMod::SHIFT;
}
bool dan::KeyMods::control() const {
    return (mods & (int)keyMod::CONTROL) == (int)keyMod::CONTROL;
}
bool dan::KeyMods::alt() const {
    return (mods & (int)keyMod::ALT) == (int)keyMod::ALT;
}
bool dan::KeyMods::super() const {
    return (mods & (int)keyMod::SUPER) == (int)keyMod::SUPER;
}
bool dan::KeyMods::capsLock() const {
    return (mods & (int)keyMod::CAPS_LOCK) == (int)keyMod::CAPS_LOCK;
}
bool dan::KeyMods::numLock() const {
    return (mods & (int)keyMod::NUM_LOCK) == (int)keyMod::NUM_LOCK;
}
