#include "PatternVars.h"

dan::api::PatternVars::PatternVars(sol::table table): luaTable(table) {
    init();
}

dan::api::PatternVars::symTable_t &dan::api::PatternVars::getTable() {
    return symTable;
}

void dan::api::PatternVars::init() {
    for (auto &v : luaTable) {
        if (v.second.is<float>() && v.first.is<std::string>()) {
            std::string name = v.first.as<std::string>();
            float value = v.second.as<float>();
            buffer[name] = value;
            // Just make sure that it exists
            symTable.add_variable(name, buffer[name]);
        }
    }
}

void dan::api::PatternVars::push() {
    for (auto &v : buffer) {
        auto t = luaTable[v.first];
        if (t.get_type() == sol::type::number) {
            v.second = t.get<float>();
        }
    }
}
void dan::api::PatternVars::pull() {
    for (auto &v : buffer) {
        luaTable[v.first].set(v.second);
    }
}

// Static members

void dan::api::PatternVars::open(sol::state_view &lua) {
    sol::usertype<PatternVars> type = lua.new_usertype<PatternVars>("PatternVars",
        sol::constructors<PatternVars(sol::table)>()
    );

    type["push"] = &PatternVars::push;
    type["pull"] = &PatternVars::pull;
}
