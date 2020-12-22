#ifndef DAN_API_PATTERN_H_INCLUDED
#define DAN_API_PATTERN_H_INCLUDED

#include <string>

#include <sol/sol.hpp>
#include <arashpartow/exprtk.hpp>

namespace dan::api {
    class Pattern {
        typedef exprtk::symbol_table<float> symbolTable_t;
        typedef exprtk::expression<float> expression_t;
        typedef exprtk::parser<float> parser_t;

        symbolTable_t symbols;
        expression_t expression;

    public:
        Pattern(sol::this_state l, const std::string &pattern, sol::variadic_args patternVars);

        // foo[fef]
        float index(const std::string &name);
        // foo[fef] = bar
        void newIndex(const std::string &name, float value);

        float run();

        static void open(sol::state_view &lua);
    };
}

#endif