#ifndef DANZUN_KEYMODS_H_INCLUDED
#define DANZUN_KEYMODS_H_INCLUDED

namespace dan {
    class KeyMods {
        int mods;
    public:
        KeyMods(int mods = 0);
        bool shift() const;
        bool control() const;
        bool alt() const;
        bool super() const;
        bool capsLock() const;
        bool numLock() const;
    };
}

#endif
