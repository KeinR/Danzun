#ifndef DANZUN_API_PATTERN_H_INCLUDED
#define DANZUN_API_PATTERN_H_INCLUDED

#include <string>

#include <sol/sol.hpp>
#include <arashpartow/exprtk.hpp>

namespace dan::api {
    /**
     * An expression parser for use by clients
     * */
    class Pattern {
        /// Type of the symbol table
        typedef exprtk::symbol_table<float> symbolTable_t;
        /// Type of the expression
        typedef exprtk::expression<float> expression_t;
        /// type of the parser
        typedef exprtk::parser<float> parser_t;

        /// The symbols
        symbolTable_t symbols;
        /// The expression
        expression_t expression;
        /// The fail state
        bool failed;

    public:
        Pattern(sol::this_state l, const std::string &pattern, sol::variadic_args patternVars);

        // foo[fef]
        float index(const std::string &name);
        // foo[fef] = bar
        void newIndex(const std::string &name, float value);
        void newIndexBool(const std::string &name, bool value);

        /**
         * Checks if the expression failed to compile or is otherwise invalid
         * \return true if yes
         * */
        bool isFailed();

        /**
         * Executes the expression
         * \return The result of the expression (last value on stack)
         * */
        float run();

        /**
         * Registers this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view &lua);
    };
}

#endif
