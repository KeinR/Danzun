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
    private:
        sol::table luaTable;
        std::unordered_map<std::string, float> buffer;
        symTable_t symTable;

        void init();
    public:
        PatternVars(sol::table table);

        symTable_t &getTable();

        void push();
        void pull();

        static void open(sol::state_view &lua);
    };
}

#endif
