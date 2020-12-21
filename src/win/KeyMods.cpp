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
