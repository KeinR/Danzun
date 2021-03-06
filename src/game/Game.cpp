#include "Game.h"

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
    speed(1),
    running(false),
    width(e.getWindow().getWidth()),
    height(e.getWindow().getHeight()),
    x(0),
    y(0),
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

dan::Game::pkeys_t &dan::Game::getUpKeys() {
    return upKeys;
}
dan::Game::pkeys_t &dan::Game::getDownKeys() {
    return downKeys;
}
dan::Game::pkeys_t &dan::Game::getLeftKeys() {
    return leftKeys;
}
dan::Game::pkeys_t &dan::Game::getRightKeys() {
    return rightKeys;
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

void dan::Game::addSpeaker(const speaker_t &speaker) {
    speakers.insert(speaker);
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
    for (renderQueue_t::iterator it = renderQueue.begin(); it != renderQueue.end();) {
        if (it->second.get() == rend) {
            it = renderQueue.erase(it);
        } else {
            ++it;
        }
    }
}

void dan::Game::setWidth(int w) {
    width = w;
}
void dan::Game::setHeight(int h) {
    height = h;
}
void dan::Game::setX(int x) {
    this->x = x;
}
void dan::Game::setY(int y) {
    this->y = y;
}
void dan::Game::setGCFactor(float f) {
    gcFactor = f;
}
void dan::Game::setGCConstant(float c) {
    gcConstant = c;
}
void dan::Game::setRunning(bool v) {
    running = v;
}
void dan::Game::setSpeed(float v) {
    speed = v;
}



int dan::Game::getWidth() {
    return width;
}
int dan::Game::getHeight() {
    return height;
}
int dan::Game::getX() {
    return x;
}
int dan::Game::getY() {
    return y;
}
float dan::Game::getGCFactor() {
    return gcFactor;
}
float dan::Game::getGCConstant() {
    return gcConstant;
}
bool dan::Game::isRunning() {
    return running;
}
float dan::Game::getSpeed() {
    return speed;
}

void dan::Game::setGCTimeMilliseconds(unsigned int v) {
    gcTimer.setTime(v);
    gcTimer.start();
}

unsigned int dan::Game::getGCTimeMilliseconds() {
    return gcTimer.getTime();
}

bool dan::Game::arePressed(const pkeys_t &keys) {
    for (dan::keyt k : keys) {
	if (engine->getWindow().keyPressed(k)) {
	    return true;
	}
    }
    return false;
}

void dan::Game::logic(float deltaTime) {
    if (!running) return;

    deltaTime *= speed;

    clock.pushDeltaTime(deltaTime);

    if (gcTimer.done()) {
        gc();
        gcTimer.start();
    }

    Player::dir d;
    d.up = arePressed(upKeys);
    d.down = arePressed(downKeys);
    d.left = arePressed(leftKeys);
    d.right = arePressed(rightKeys);
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
        p.second.invalidate();
    }
}

void dan::Game::gc() {

    // Clean up speaker references
    for (speakers_t::iterator it = speakers.begin(); it != speakers.end();) {
        if (!(*it)->isPlaying()) {
            it = speakers.erase(it);
        } else {
            ++it;
        }
    }

    // Clean up entity references
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

    engine->collectGarbage();
}

void dan::Game::render(Context &c) {
    for (auto &p : renderQueue) {
        p.second->render(c);
    }
}

dan::Game &dan::Game::fromLua(sol::state_view lua) {
    return Engine::fromLua(lua).getGame();
}
