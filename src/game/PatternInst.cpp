#include "PatternInst.h"

#include "Game.h"
#include "../core/Engine.h"
#include "Pattern.h"

dan::PatternInst::PatternInst(): pattern(nullptr), switchTime(0), index(0) {
}
dan::PatternInst::PatternInst(Game &g, Pattern &pattern):
    symbols(pattern.getParams()), switchTime(g.getEngine().getContext().getClock().getTime() + pattern.getRuns()[0].first), index(0)
{
}
void dan::PatternInst::setParam(const std::string &name, float value) {
    symbols.add_constant(name, value);
}
dan::PatternInst::runresult_t dan::PatternInst::run(Game &g) {
    if (g.getEngine().getContext().getClock().getTime() > switchTime && index + 1 < pattern->getRuns().size()) {
        index++;
        switchTime = g.getEngine().getContext().getClock().getTime() + pattern->getRuns()[index].first;
    }
    runresult_t result;
    Pattern::rungroup_t &gps = pattern->getRuns()[index].second;
    for (std::pair<std::string, Pattern::expression_t> &g : gps) {
        // Internally copies the symbol tables anyways, so there's not much of a difference here.
        // Kinda' a hack ig but it works.
        g.second.get_symbol_table(0) = symbols;
        float value = g.second.value();
        symbols.add_constant(g.first, value);
        result.emplace_back(g.first, value);
    }
    return result;
}
