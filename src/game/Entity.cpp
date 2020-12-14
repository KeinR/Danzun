#include "Entity.h"

#include "../time/Clock.h"

dan::Entity::Entity():
    pos{0, 0},
    startingTime(0),
    rotation(0),
    width(10),
    height(10),
    autoGC(true),
    gc(false)
{
}
dan::Entity::Entity(Game &g, sol::function hitCallback, const disp_t &disp, const std::string &equation, float x, float y, float width, float height, bool autoGC):
    type(type),
    pos{x, y},
    startingTime(g.getClock().getTime()),
    rotation(0),
    width(width),
    height(height),
    autoGC(autoGC),
    gc(false),
    disp(disp),
    hitCallback(hitCallback)
{
    setEquation(g, equation);
}

void dan::Entity::setParam(const std::string &name, const std::vector<float> &vector) {
    symbols.add_constant(name, vector);
}
void dan::Entity::setParam(const std::string &name, float value) {
    symbols.add_constant(name, value);
}
void dan::Entity::setParam(const std::string &name, const std::string &string) {
    symbols.add_constant(name, string);
}

void dan::Entity::initEquation(Game &g, const std::string &eq) {

    symbols.add_vector("p", currentPosition.data(), currentPosition.size());
    symbols.add_variable("ti", startingTime);
    symbols.add_variable("rot", rotation);
    symbols.add_variable("width", width);
    symbols.add_variable("height", height);
    symbols.add_variable("autoGC", autoGC);
    symbols.add_variable("gc", gc);

    // A little dangerous I will admit, but it really helps the flow
    symbols.add_variable("t", g.getClock().getTime(), true);
    symbols.add_variable("dt", g.getClock().getDeltaTime(), true);
    // I don't see a way in exprtk to make vectors const. Oh well, guess entities get to change the player's position...
    symbols.add_variable("plp", g.getPlayer().getPos().data(), g.getPlayer().getPos().size());

    symbols.add_constants();

    expression.register_symbol_table(symbols);

    parser_t parser;
    if (parser.compile(eq, expression)) {
        // TEMP - should notify once then ignore, not spam console
        std::cerr << "Failed to compile expression, " << parser.error() << '\n';
    }
}

bool dan::Entity::isGC() {
    return gc;
}

bool dan::Entity::isAutoGC() {
    return autoGC;
}

sol::function getHitCallback() {
    return hitCallback;
}

void dan::Entity::run() {
    expression.value();
}

void dan::Entity::render(Context &c) {
    disp->setup(c);

    Matrix mat;
        mat.x = currentPosition[0];
        mat.y = currentPosition[1];
        mat.width = width;
        mat.height = height;
        mat.rotation = rotation;
    mat.load(c);

    disp->render(c);
}
