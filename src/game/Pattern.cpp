#include "Pattern.h"

dan::Pattern::Pattern() {
}
dan::Pattern::Pattern(const rawParams_t &rawParams, const rawRuns_t &rawRuns) {
    setParams(rawParams);
    setRuns(rawRuns);
}

void dan::Pattern::setParams(const rawParams_t &rawParams) {
    for (std::pair<std::string, float> &p : rawParams) {
        params.add_constant(p.first, p.second);
    }
    params.add_constant("pi", 3.14159);
    params.add_constants();
}
void dan::Pattern::setRuns(const rawRuns_t &rawRuns) {
    exprtk::parser<float> parser;
    runs.reserve(rawRuns.size());
    for (std::pair<float, std::string> &r : rawRuns) {
        runs.emplace_back();
        runs.back().first = r.first;
        for (std::pair<std::string, std::string> &v : runs.back().second) {
            runs.back().emplace_back();
            runs.back().back().first = r.first;
            runs.back().back().second = r.first;
            parser.compile(r.second, runs.back().back().second);
            runs.back().back().second.register_symbol_table(params);
        }
    }
}
dan::Pattern::params_t &dan::Pattern::getParams() {
    return params;
}
dan::Pattern::runs_t &dan::Pattern::getRuns() {
    return runs;
}
