#ifndef DANZUN_API_PATTERNVARS_H_INCLUDED
#define DANZUN_API_PATTERNVARS_H_INCLUDED

#include <unordered_map>
#include <string>

#include <sol/sol.hpp>
#include <arashpartow/exprtk.hpp>

namespace dan::api {
    class PatternVars {
    public:
        typedef exprtk::symbol_table<float> symTable_t;
	typedef exprtk::function_compositor<float> compositor_t;
    private:
	typedef typename compositor_t::function function_t;

        sol::table luaTable;
        std::unordered_map<std::string, float> buffer;
        symTable_t symTable;
	compositor_t compositor;

        void init();
    public:
        PatternVars(sol::table table);

        symTable_t &getTable();

        void push();
        void pull();
	void addFunction(const std::string &name, const std::string &body, sol::variadic_args params);

        static void open(sol::state_view &lua);
    };
}

#endif
