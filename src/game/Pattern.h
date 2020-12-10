#ifndef DANZUN_PATTERN_H_INCLUDED
#define DANZUN_PATTERN_H_INCLUDED

#include <vector>
#include <utility>
#include <string>

#include <arashpartow/exprtk.hpp>

namespace dan {
    class Pattern {
    public:
        typedef exprtk::expression<float> expression_t;
        typedef exprtk::symbol_table<float> params_t;
        // time, [variable, expression]
        typedef std::vector<std::pair<std::string, expression_t>> rungroup_t;
        typedef std::vector<std::pair<float, rungroup_t>> runs_t;

        typedef std::vector<std::pair<std::string, float>> rawParams_t;
        // [time, [variables, [name, expression]]]
        typedef std::vector<std::pair<float, std::vector<std::pair<std::string, std::string>>>> rawRuns_t;
    private:
        // Explicit parameters
        params_t params;
        runs_t runs;
    public:
        Pattern();
        Pattern(const rawParams_t &rawParams, const rawRuns_t &rawRuns);
        void setParams(const rawParams_t &rawParams);
        void setRuns(const rawRuns_t &rawRuns);
        params_t &getParams();
        runs_t &getRuns();
    };
}

#endif
