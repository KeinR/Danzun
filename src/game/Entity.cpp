#include "Entity.h"

#include "../core/debug.h"
#include "../core/error.h"
#include "../core/Engine.h"
#include "../game/Game.h"
#include "../time/Clock.h"
#include "../api/Entity.h"

dan::Entity::Entity(
    Game &g, sol::function hitCallback, const disp_t &disp,
    const std::string &equation, const std::vector<symbolTable_t> &as
):
    pos{0, 0},
    startingTime(g.getClock().getTime()),
    rotation(0),
    width(30),
    height(30),
    autoGC(b2f(true)),
    gc(b2f(false)),
    display(b2f(true)),
    tangible(b2f(true)),
    disp(disp),
    hitCallback(hitCallback),
    renderPriority(0)
{
    initEquation(g, as, equation);
}

// Static
std::shared_ptr<dan::Entity> dan::Entity::make(Game &g, sol::function hitCallback, const disp_t &disp, const std::string &equation,
        const std::vector<symbolTable_t> &as)
{
    std::shared_ptr<Entity> result = std::make_shared<Entity>(g, hitCallback, disp, equation, as);
    result->self = result;
    return result;
}

dan::Entity::symbolTable_t &dan::Entity::getTable() {
    return symbols;
}

int dan::Entity::getX() const {
    return pos[0];
}
int dan::Entity::getY() const {
    return pos[1];
}
int dan::Entity::getWidth() const {
    return width;
}
int dan::Entity::getHeight() const {
    return height;
}
float dan::Entity::getRotation() const {
    return rotation;
}

int dan::Entity::getRenderPriority() {
    return renderPriority;
}
void dan::Entity::setRenderPriority(int value) {
    renderPriority = value;
}

std::set<std::string> &dan::Entity::getGroups() {
    return groups;
}

void dan::Entity::setScript(const api::Script &s) {
    this->script = s;
}

void dan::Entity::initEquation(Game &g, const std::vector<symbolTable_t> &as, const std::string &eq) {

    symbols.add_vector("p", pos.data(), pos.size());
    symbols.add_variable("x", pos[0]);
    symbols.add_variable("y", pos[1]);
    symbols.add_variable("ti", startingTime);
    symbols.add_variable("rot", rotation);
    symbols.add_variable("width", width);
    symbols.add_variable("height", height);
    symbols.add_variable("autoGC", autoGC);
    symbols.add_variable("gc", gc);
    symbols.add_variable("disp", display);
    symbols.add_variable("tang", tangible);

    symbols.add_constants();

    exp.register_symbol_table(symbols);

    for (symbolTable_t table : as) {
        exp.register_symbol_table(table);
    }

    parser_t parser;
    parser.enable_unknown_symbol_resolver();

    if (!parser.compile(eq, exp)) {
        err("Entity::initEquation", g.getEngine().getState()) << "Failed to compile expression: " << parser.error();
    }
}

bool dan::Entity::f2b(float f) {
    return static_cast<bool>(f);
}
float dan::Entity::b2f(bool b) {
    return static_cast<float>(b);
}

bool dan::Entity::isGC() {
    return f2b(gc);
}

bool dan::Entity::isAutoGC() {
    return f2b(autoGC);
}

bool dan::Entity::isTangible() {
    return f2b(tangible);
}

sol::function dan::Entity::getHitCallback() {
    return hitCallback;
}

void dan::Entity::run(sol::state_view lua) {
    exp.value();
    script.run(lua.lua_state());
}

void dan::Entity::render(Context &c) {
    if (disp && f2b(display)) {
        // disp cannot have ref to `this` else `this` would never destruct.
        // Therefore, it must be passed as arg
        disp->augRender(::dan::api::Entity(self.lock()));
    }
}
