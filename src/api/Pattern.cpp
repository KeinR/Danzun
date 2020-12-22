#include "Pattern.h"

#include <stdexcept>

#include "../game/Game.h"
#include "PatternVars.h"

dan::api::Pattern::Pattern(sol::this_state l, const std::string &pattern, sol::variadic_args patternVars) {

    expression.register_symbol_table(symbols);

    for (auto o : patternVars) {
        // Unchecked danger
        expression.register_symbol_table(o.as<PatternVars>().getTable());
    }

    expression.register_symbol_table(Game::fromLua(l).getGlobalSymbols());

    parser_t parser;
    parser.enable_unknown_symbol_resolver();

    if (!parser.compile(pattern, expression)) {
        throw std::runtime_error("Failed to compile expression: " + parser.error());
    }

}

float dan::api::Pattern::index(const std::string &name) {
    auto *v = symbols.get_variable(name);
    return v == nullptr ? 0 : v->value();
}
void dan::api::Pattern::newIndex(const std::string &name, float value) {
    auto *v = symbols.get_variable(name);
    if (v != nullptr) {
        v->ref() = value;
    }
}

float dan::api::Pattern::run() {
    return expression.value();
}

void dan::api::Pattern::open(sol::state_view &lua) {
    sol::usertype<Pattern> type = lua.new_usertype<Pattern>("Pattern",
        sol::constructors<Pattern(sol::this_state,const std::string&,sol::variadic_args)>()
    );

    type[sol::meta_function::index] = &Pattern::index;
    type[sol::meta_function::new_index] = &Pattern::newIndex;
    type[sol::meta_function::call] = &Pattern::run;
    type["run"] = &Pattern::run;
}