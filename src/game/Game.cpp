#include "Game.h"

#include "Player.h"

#include "../core/debug.h"

static constexpr unsigned int eofs = 1;
static constexpr unsigned int playeri = 0;

dan::Game::Game():
    // Player is stored in index 1
    entities(eofs)
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
            result.push_back(i);
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
        e->logic(*this, deltaTime);
    }
    for (bulletType_t &b : enemyBullets) {
        b->logic(*this, deltaTime, false);
    }
    for (bulletType_t &b : allyBullets) {
        b->logic(*this, deltaTime, true);
    }
}
void dan::Game::render(Context &c) {
    DANZUN_ASSERT(entities[playeri]); // Make sure player is set

    for (entity_t &e : entities) {
        e->render(c);
    }
    for (bulletType_t &b : enemyBullets) {
        b->render(*this, c);
    }
    for (bulletType_t &b : allyBullets) {
        b->render(*this, c);
    }
}
