#include "Entity.h"

#include "../core/debug.h"
#include "../game/Game.h"
#include "../time/Clock.h"
#include "../render/Matrix.h"
#include "../api/Entity.h"

dan::Entity::Entity(
    Game &g, sol::function hitCallback, const disp_t &disp,
    const std::string &equation, const std::vector<symbolTable_t> &as,
    const constants_t &constants,
    float x, float y, float width, float height, bool autoGC
):
    pos{x, y},
    startingTime(g.getClock().getTime()),
    rotation(0),
    width(width),
    height(height),
    autoGC(b2f(autoGC)),
    gc(b2f(false)),
    disp(disp),
    hitCallback(hitCallback)
{
    DANZUN_ASSERT(disp); // Just in case...
 
    initEquation(as, constants, equation);
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

void dan::Entity::setScript(const std::shared_ptr<Entity> &self, sol::state_view lua, sol::function func, const std::vector<sol::object> &params) {
    DANZUN_ASSERT(self.get() == this); // Must be the same object, just as a shared ptr.
    // Perhaps instead use factory and store weak_ptr to self? Would be safer... Hmm...

    std::vector<sol::object> p = params;
    p.insert(p.begin(), sol::make_object<api::Entity>(lua, self));
    this->script = api::Script(lua, func, p);
}

void dan::Entity::setParam(const std::string &name, float value) {
    symbols.add_constant(name, value);
}

void dan::Entity::regSymbolTable(symbolTable_t &table) {
    exp.register_symbol_table(table);
}

void dan::Entity::initEquation(const std::vector<symbolTable_t> &as, const constants_t &constants, const std::string &eq) {

    symbols.add_vector("p", pos.data(), pos.size());
    symbols.add_variable("x", pos[0]);
    symbols.add_variable("y", pos[1]);
    symbols.add_variable("ti", startingTime);
    symbols.add_variable("rot", rotation);
    symbols.add_variable("width", width);
    symbols.add_variable("height", height);
    symbols.add_variable("autoGC", autoGC);
    symbols.add_variable("gc", gc);

    for (const std::pair<std::string, float> &c : constants) {
        symbols.add_constant(c.first, c.second);
    }

    // I don't see a way in exprtk to make vectors const. Oh well, guess entities get to change the player's position...
    // [[ PLAYER NOT YET IMPLEMENTED ]]
    // symbols.add_variable("plp", g.getPlayer().getPos().data(), g.getPlayer().getPos().size());

    symbols.add_constants();

    exp.register_symbol_table(symbols);

    for (symbolTable_t table : as) {
        exp.register_symbol_table(table);
    }

    parser_t parser;
    if (!parser.compile(eq, exp)) {
        // TEMP - should notify once then ignore, not spam console
        std::cerr << "Entity: Failed to compile expression, " << parser.error() << '\n';
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

sol::function dan::Entity::getHitCallback() {
    return hitCallback;
}

void dan::Entity::run(sol::state_view lua) {
    exp.value();
    script.run(lua.lua_state());
}

void dan::Entity::render(Context &c) {
    disp->setup(c);

    Matrix mat;
        mat.x = pos[0];
        mat.y = pos[1];
        mat.width = width;
        mat.height = height;
        mat.rotation = rotation;
    mat.load(c);

    disp->render(c);
}
