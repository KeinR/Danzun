#include "Entity.h"

#include "../time/Clock.h"
#include "../game/Game.h"
#include "../render/Matrix.h"

dan::Entity::Entity(Game &g, sol::function hitCallback, const disp_t &disp, const std::string &equation, float x, float y, float width, float height, bool autoGC):
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
    initEquation(g, equation);
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
int dan::Entity::getRotation() const {
    return rotation;
}

void dan::Entity::setParam(const std::string &name, float value) {
    symbols.add_constant(name, value);
}

void dan::Entity::initEquation(Game &g, const std::string &eq) {

    symbols.add_vector("p", pos.data(), pos.size());
    symbols.add_variable("ti", startingTime);
    symbols.add_variable("rot", rotation);
    symbols.add_variable("width", width);
    symbols.add_variable("height", height);
    symbols.add_variable("autoGC", autoGC);
    symbols.add_variable("gc", gc);

    // A little dangerous I will admit, but it really helps the flow
    symbols.add_variable("t", g.getClock().getTimeRef(), true);
    symbols.add_variable("dt", g.getClock().getDeltaTimeRef(), true);
    // I don't see a way in exprtk to make vectors const. Oh well, guess entities get to change the player's position...
    // NOT IMPLEMENTED
    // symbols.add_variable("plp", g.getPlayer().getPos().data(), g.getPlayer().getPos().size());

    symbols.add_constants();

    exp.register_symbol_table(symbols);

    parser_t parser;
    if (parser.compile(eq, exp)) {
        // TEMP - should notify once then ignore, not spam console
        std::cerr << "Failed to compile expression, " << parser.error() << '\n';
    }
}

bool dan::Entity::f2b(float f) {
    return f > 0;
}
float dan::Entity::b2f(bool b) {
    return b ? 1 : -1;
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

void dan::Entity::run() {
    exp.value();
}

void dan::Entity::render(Context &c) {
    disp->setup();

    Matrix mat;
        mat.x = pos[0];
        mat.y = pos[1];
        mat.width = width;
        mat.height = height;
        mat.rotation = rotation;
    mat.load(c);

    disp->render();
}
