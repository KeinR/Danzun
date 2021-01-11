#ifndef DANZUN_API_PATTERNVARS_H_INCLUDED
#define DANZUN_API_PATTERNVARS_H_INCLUDED

#include <unordered_map>
#include <string>

#include <sol/sol.hpp>
#include <arashpartow/exprtk.hpp>

namespace dan::api {
    /**
     * A set of variables that can be attached to multible expressions.
     * */
    class PatternVars {
    public:
        /// The symbol table type
        typedef exprtk::symbol_table<float> symTable_t;
        /// The function compositor type
	typedef exprtk::function_compositor<float> compositor_t;
    private:
	typedef typename compositor_t::function function_t;

        /// The lua table with lua's copy of the variables
        sol::table luaTable;
        /// The intermediate buffer that maintains constant references to the variables
        std::unordered_map<std::string, float> buffer;
        /// The symbol table itself
        symTable_t symTable;
        /// The function compositor
	compositor_t compositor;

        /**
         * Initialize the table
         * */
        void init();
    public:
        /**
         * Create with a table of variables
         * \param table The variables
         * \note Any variables that are not numbers are ignored
         * */
        PatternVars(sol::table table);

        /**
         * Gets the internal symbol table
         * */
        symTable_t &getTable();

        /**
         * Write the values in the lua table to the buffer so that
         * they reflect in the expression table.
         * */
        void push();
        /**
         * Write the values in the buffer to the lua table
         * */
        void pull();
        /**
         * Adds a callable function
         * \param name The name
         * \param body The body of the function
         * \oaram params Scalar arguments taken by the function, in order
         * */
	void addFunction(const std::string &name, const std::string &body, sol::variadic_args params);

        /**
         * Registers this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view &lua);
    };
}

#endif
