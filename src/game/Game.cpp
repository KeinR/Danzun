#include "Game.h"

#include "Player.h"

#include "../core/debug.h"

static constexpr unsigned int eofs = 1;
static constexpr unsigned int playeri = 0;

dan::Game::Game():
    // Player is stored in index 1
    entities(eofs),
    // Clean up entities every ~5 seconds
    // (Not happening much, as there aren't many entities...)
    gcTimer(5000),
    autoGC(true)
{
}

void dan::Game::setWidth(int w) {
    width = w;
}
void dan::Game::setHeight(int h) {
    height = h;
}

void dan::Game::setPlayer(const player_t &p) {
    entities[playeri] = p;
    player = p;
}

dan::Game::player_t dan::Game::getPlayer() const {
    return player;
}

void dan::Game::addEntity(const entity_t &e) {
    entities.push_back(e);
}

int dan::Game::getWidth() {
    return width;
}
int dan::Game::getHeight() {
    return height;
}

std::vector<unsigned int> dan::Game::getLocalEntities(const hitbox_t &, bool allied) {
    // TEMP SOLUTION
    std::vector<unsigned int> result;
    if (allied) {
        for (unsigned int i = eofs; i < entities.size(); i++) {
            if (!entities[i]->shouldDelete()) {
                result.push_back(i);
            }
        }
    } else {
        result.push_back(playeri);
    }
    return result;
}
dan::Entity &dan::Game::getEntity(unsigned int index) {
    return *entities[index];
}

void dan::Game::pushEnemyBulletType(const bulletType_t &type) {
    enemyBullets.push_back(type);
}
void dan::Game::pushAllyBulletType(const bulletType_t &type) {
    allyBullets.push_back(type);
}
void dan::Game::logic(float deltaTime) {
    DANZUN_ASSERT(entities[playeri]); // Make sure player is set

    // ... TODO: update entity map ...

    for (entity_t &e : entities) {
        if (!e->shouldDelete()) {
            e->logic(*this, deltaTime);
        }
    }
    for (bulletType_t &b : enemyBullets) {
        b->logic(*this, deltaTime, false);
    }
    for (bulletType_t &b : allyBullets) {
        b->logic(*this, deltaTime, true);
    }

    if (gcTimer.done()) {
        gc();
        gcTimer.start();
    }
}

void dan::Game::gc() {
    typedef entities_t::iterator iterator;
    for (iterator it = entities.begin(); it < entities.end();) {
        if ((*it)->shouldDelete() || (autoGC && (*it)->getHitbox().getMinY() > getHeight())) {
            it = entities.erase(it);
        } else {
            ++it;
        }
    }
}

void dan::Game::render(Context &c) {
    DANZUN_ASSERT(entities[playeri]); // Make sure player is set

    for (entity_t &e : entities) {
        if (!e->shouldDelete()) {
            e->render(c);
        }
    }
    for (bulletType_t &b : enemyBullets) {
        b->renderChildren(*this, c);
    }
    for (bulletType_t &b : allyBullets) {
        b->renderChildren(*this, c);
    }
}
