#ifndef DANZUN_PATTERNINST_H_INCLUDED
#define DANZUN_PATTERNINST_H_INCLUDED

#include <vector>
#include <utility>

#include "Pattern.h"

namespace dan {
    class Game;
}

namespace dan {
    class PatternInst {
    public:
        typedef std::vector<std::pair<std::string, float>> runresult_t;
    private:
        Pattern *pattern;
        Pattern::params_t symbols;
        float switchTime;
        unsigned int index;
        // int entityId;
    public:
        PatternInst();
        PatternInst(Game &g, Pattern &pattern);
        void setParam(const std::string &name, float value);
        // Returns in order of exports defined in `pattern`
        runresult_t run(Game &g);
    };
}

#endif
