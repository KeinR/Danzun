#include "PatternInst.h"

dan::PatternInst::PatternInst(Game &g, Pattern &pattern):
    symbols(pattern.getParams()), switchTime(g.getTime() + pattern->getRuns()[0].first), index(0)
{
}
void dan::PatternInst::setParam(const std::string &name, float value) {
    symbols.set_constant(name, value);
}
runresult_t dan::PatternInst::run(Game &g) {
    if (g.getTime() > switchTime && index + 1 < pattern->getRuns().size()) {
        index++;
        switchTime = g.getTime() + pattern->getRuns()[index].first;
    }
    runresult_t result;
    Pattern::rungroup_t &gps = pattern->getRuns()[index].second;
    for (std::pair<std::string, Pattern::expression_t> &g : gps) {
        // Internally copies the symbol tables anyways, so there's not much of a difference here.
        // Kinda' a hack ig but it works.
        g.second.get_symbol_table(0) = symbols;
        float value = g.second.value();
        symbols.set_constant(g.first, value);
        result.emplace_back(g.first, value);
    }
    return result;
}
