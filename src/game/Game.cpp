#include "Game.h"

#include <iostream>

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
    gcFactor(1.5),
    gcConstant(50),
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

dan::Game::entities_t::iterator dan::Game::eraseEntity(const entities_t::iterator &it) {
    for (const std::string &name : (*it)->getGroups()) {
        getGroup(name).erase(it->get());
    }
    (*it)->getGroups().clear();

    removeRenderable(it->get());

    return entities.erase(it);
}

void dan::Game::remFromGroups(Entity *ptr) {
    for (auto &p : groups) {
        p.second.erase(ptr);
    }
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

void dan::Game::addEntity(const entity_t &e) {
    entities.push_back(e);
}

void dan::Game::submitRenderable(int priority, const renderable_t &rend) {
    renderQueue.insert({priority, rend});
}
void dan::Game::removeRenderable(Renderable *rend) {
    remRenderQueue.insert(rend);
}

void dan::Game::setWidth(int w) {
    width = w;
}
void dan::Game::setHeight(int h) {
    height = h;
}
void dan::Game::setGCFactor(float f) {
    gcFactor = f;
}
void dan::Game::setGCConstant(float c) {
    gcConstant = c;
}



int dan::Game::getWidth() {
    return width;
}
int dan::Game::getHeight() {
    return height;
}
float dan::Game::getGCFactor() {
    return gcFactor;
}
float dan::Game::getGCConstant() {
    return gcConstant;
}

void dan::Game::setGCTimeMilliseconds(unsigned int v) {
    gcTimer.setTime(v);
    gcTimer.start();
}

unsigned int dan::Game::getGCTimeMilliseconds() {
    return gcTimer.getTime();
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
        entity_t &e = *it;
        if (e->isGC()) {
            it = eraseEntity(it);
        } else {
            e->run(lua);
            ++it;
        }
    }

    for (auto &p : groups) {
        p.second.update();
    }
}

void dan::Game::gc() {
    for (entities_t::iterator it = entities.begin(); it != entities.end();) {
        entity_t &e = *it;
        if (e->isAutoGC()) {
            float x = e->getX();
            float y = e->getY();
            float major = e->getWidth() * gcFactor + gcConstant; // x
            float minor = e->getHeight() * gcFactor + gcConstant; // y
            float left = x - major;
            float right = x + major;
            float top = y - minor;
            float bottom = y + minor;
            if (right < 0 || left > width || bottom < 0 || top > height) {
                it = eraseEntity(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}

void dan::Game::render(Context &c) {
    if (!remRenderQueue.empty()) {
        for (renderQueue_t::iterator it = renderQueue.begin(); it != renderQueue.end();) {
            if (remRenderQueue.find(it->second.get()) != remRenderQueue.end()) {
                it = renderQueue.erase(it);
            } else {
                ++it;
            }
        }
        remRenderQueue.clear();
    }
    for (auto &p : renderQueue) {
        p.second->render(c);
    }
}

dan::Game &dan::Game::fromLua(sol::state_view lua) {
    return Engine::fromLua(lua).getGame();
}
