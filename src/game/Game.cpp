#include "Game.h"

#include "../core/debug.h"
#include "../core/Engine.h"

template <typename T>
struct PrintFunc : public exprtk::igeneric_function<T> {
    typedef typename exprtk::igeneric_function<T>::parameter_list_t parameter_list_t;
    typedef typename exprtk::igeneric_function<T>::generic_type generic_type;

    PrintFunc()
    : exprtk::igeneric_function<T>("S")
    {}

    inline T operator()(parameter_list_t params) {
        typedef typename generic_type::string_view string_t;
        string_t string(params[0]);
        std::string str(string.begin(), string.end());
        std::cout << str << '\n';
        return T(0);
    }
};

static PrintFunc<float> printFunc;

dan::Game::Game(Engine &e):
    engine(&e),
    width(e.getWindow().getWidth()),
    height(e.getWindow().getHeight()),
    // Clean up entities every ~5 seconds
    // (Not happening much, as there aren't many entities...)
    gcTimer(5000)
{
    // A little dangerous I will admit, but it really helps the flow
    globalSymbols.add_variable("t", clock.getTimeRef(), false);
    globalSymbols.add_variable("dt", clock.getDeltaTimeRef(), false);
    globalSymbols.add_variable("px", player.getXRef());
    globalSymbols.add_variable("py", player.getYRef());
    globalSymbols.add_vector("pv", player.getPos().data(), player.getPos().size());

    globalSymbols.add_function("print", printFunc);
}

dan::Engine &dan::Game::getEngine() const {
    return *engine;
}
dan::Clock &dan::Game::getClock() {
    return clock;
}

dan::Player &dan::Game::getPlayer() {
    return player;
}

dan::Entity::symbolTable_t &dan::Game::getGlobalSymbols() {
    return globalSymbols;
}

dan::Group &dan::Game::getGroup(const std::string &name) {
    return groups[name];
}

void dan::Game::resetGroups() {
    for (auto &g : groups) {
        g.second.clear();
    }
}
void dan::Game::clearGroups() {
    groups.clear();
}

dan::Game::collisionResult_t dan::Game::testCollisions(const std::string &a, const std::string &b) {
    collisionResult_t result;
    groups[a].test(groups[b], result);
    return result;
}

dan::Game::entities_t::iterator dan::Game::deleteEntity(const entities_t::iterator &it) {
    Entity *ptr = &(*it);
    // Will only be in one collision group, however arbitrary normal groups
    for (auto &p : groups) {
        if (p.second.erase(ptr)) {
            break;
        }
    }
    removeRenderable(ptr);
    return entities.erase(it);
}

dan::Entity &dan::Game::addEntity(
    sol::function hitCallback, const Entity::disp_t &disp, const std::string &equation,
    const std::vector<Entity::symbolTable_t> &symbols, const Entity::constants_t &constants,
    float x, float y, float width, float height, bool autoGC)
{
    std::vector<Entity::symbolTable_t> s = symbols;
    s.push_back(globalSymbols);
    entities.emplace_back(*this, hitCallback, disp, equation, s, constants, x, y, width, height, autoGC);
    return entities.back();
}

void dan::Game::submitRenderable(int priority, Renderable &rend) {
    renderQueue.insert({priority, &rend});
}
void dan::Game::removeRenderable(Renderable *rend) {
    for (renderQueue_t::iterator it = renderQueue.begin(); it != renderQueue.end();) {
        if (it->second == rend) {
            it = renderQueue.erase(it);
        } else {
            ++it;
        }
    }
}

dan::Effect &dan::Game::createEffect(sol::table masterObject, sol::function callback) {
    effects.emplace_back(engine->getState(), masterObject, callback);
    return effects.back();
}
void dan::Game::deleteEffect(Effect *e) {
    for (effects_t::iterator it = effects.begin(); it != effects.end();) {
        if (&(*it) == e) {
            it = effects.erase(it);
        } else {
            ++it;
        }
    }
    removeRenderable(e);
}

void dan::Game::setWidth(int w) {
    width = w;
}
void dan::Game::setHeight(int h) {
    height = h;
}



int dan::Game::getWidth() {
    return width;
}
int dan::Game::getHeight() {
    return height;
}


void dan::Game::logic(float deltaTime) {
    clock.pushDeltaTime(deltaTime);

    if (gcTimer.done()) {
        gc();
        gcTimer.start();
    }

    Window &w = engine->getWindow();

    Player::dir d;
    d.up = w.keyPressed(keyt::UP);
    d.down = w.keyPressed(keyt::DOWN);
    d.left = w.keyPressed(keyt::LEFT);
    d.right = w.keyPressed(keyt::RIGHT);
    player.move(*this, d, deltaTime);

    sol::state_view lua = engine->getState();

    for (entities_t::iterator it = entities.begin(); it != entities.end();) {
        if (it->isGC()) {
            it = deleteEntity(it);
        } else {
            it->run(lua);
            ++it;
        }
    }

    for (auto &p : groups) {
        p.second.update();
    }
}

void dan::Game::gc() {
    for (entities_t::iterator it = entities.begin(); it != entities.end();) {
        if (it->isAutoGC()) {
            if (false) {
                // TODO
                it = deleteEntity(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}

void dan::Game::render(Context &c) {
    for (auto &p : renderQueue) {
        p.second->render(c);
    }
}

dan::Game &dan::Game::fromLua(sol::state_view lua) {
    return Engine::fromLua(lua).getGame();
}
