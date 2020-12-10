#include "Pattern.h"

dan::Pattern::Pattern() {
}
dan::Pattern::Pattern(const rawParams_t &rawParams, const rawRuns_t &rawRuns) {
    setParams(rawParams);
    setRuns(rawRuns);
}

void dan::Pattern::setParams(const rawParams_t &rawParams) {
    for (const std::pair<std::string, float> &p : rawParams) {
        params.add_constant(p.first, p.second);
    }
    params.add_constant("pi", 3.14159);
    params.add_constants();
}
void dan::Pattern::setRuns(const rawRuns_t &rawRuns) {
    exprtk::parser<float> parser;
    runs.reserve(rawRuns.size());
    for (const std::pair<float, std::vector<std::pair<std::string, std::string>>> &r : rawRuns) {
        runs.emplace_back();
        runs.back().first = r.first;
        for (const std::pair<std::string, std::string> &v : r.second) {
            runs.back().second.emplace_back();
            runs.back().second.back().first = v.first;
            parser.compile(v.second, runs.back().second.back().second);
            runs.back().second.back().second.register_symbol_table(params);
        }
    }
}
dan::Pattern::params_t &dan::Pattern::getParams() {
    return params;
}
dan::Pattern::runs_t &dan::Pattern::getRuns() {
    return runs;
}
