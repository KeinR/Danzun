#include "Pattern.h"

#include "../core/error.h"
#include "../game/Game.h"
#include "PatternVars.h"

dan::api::Pattern::Pattern(sol::this_state l, const std::string &pattern, sol::variadic_args patternVars) {

    expression.register_symbol_table(symbols);

    for (auto o : patternVars) {
        if (o.is<PatternVars>()) {
            expression.register_symbol_table(o.as<PatternVars>().getTable());
        }
    }

    // The global symbol table has the lowest priority
    expression.register_symbol_table(Game::fromLua(l).getGlobalSymbols());

    parser_t parser;
    parser.enable_unknown_symbol_resolver();

    failed = !parser.compile(pattern, expression);

    if (failed) {
        err("api::Pattern::Pattern", l) << "Failed to compile expression: " << parser.error();
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
void dan::api::Pattern::newIndexBool(const std::string &name, bool value) {
    newIndex(name, static_cast<float>(value));
}

bool dan::api::Pattern::isFailed() {
    return failed;
}

float dan::api::Pattern::run() {
    return expression.value();
}

void dan::api::Pattern::open(sol::state_view &lua) {
    sol::usertype<Pattern> type = lua.new_usertype<Pattern>("Pattern",
        sol::constructors<Pattern(sol::this_state,const std::string&,sol::variadic_args)>()
    );

    type[sol::meta_function::index] = &Pattern::index;
    type[sol::meta_function::new_index] = sol::overload(&Pattern::newIndex, &Pattern::newIndexBool);
    type[sol::meta_function::call] = &Pattern::run;

    type["run"] = &Pattern::run;
    type["failed"] = sol::property(&Pattern::isFailed);
}
