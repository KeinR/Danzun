#include "BulletType.h"

#include "../lib/glfw.h"

#include "../math/Circle.h"

#include "Game.h"

dan::BulletType::BulletType():
    // Run GC every ~100 ms
    gcTimer(100),
    time(0.0f),
    autoGC(true),
    teamId(0)
{
}

void dan::BulletType::setSprite(const Sprite &s) {
    sprite = s;
}
dan::Sprite &dan::BulletType::getSprite() {
    return sprite;
}

void dan::BulletType::setHitbox(const hitbox_t &hb) {
    hitbox = hb;
}
void dan::BulletType::setViewHitbox(const hitbox_t &hb) {
    viewHitbox = hb;
}

void dan::BulletType::setTeamID(int id) {
    teamId = id;
}

void dan::BulletType::addChild(const glm::vec2 &position, const glm::vec2 &velocity, float rotation) {
    children.push_back(child{
        position,
        velocity,
        position,
        rotation,
        time,
        false
    });
}
void dan::BulletType::gc(Game &g) {
    typedef children_t::iterator iterator;
    // TODO: Batch deletions, or just run infrequently
    for (iterator it = children.begin(); it < children.end();) {
        if (it->gc) {
            it = children.erase(it);
        } else if (autoGC) {
            viewHitbox->setX(it->position.x);
            viewHitbox->setY(it->position.y);
            viewHitbox->setRotation(it->rotation);
            viewHitbox->load();
            if (
                // Outside of viewport and not showing an intent to return
                (viewHitbox->getMaxX() < 0 && it->velocity.x <= 0) ||
                (viewHitbox->getMinX() > g.getWidth() && it->velocity.x >= 0) ||
                (viewHitbox->getMaxY() < 0 && it->velocity.y <= 0) ||
                (viewHitbox->getMinY() > g.getHeight() && it->velocity.y >= 0)
            ) {
                it = children.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }    
}
void dan::BulletType::logic(Game &g, float deltaTime) {
    for (child &c : children) {
        if (!c.gc) {
            hitbox->setX(c.position.x);
            hitbox->setY(c.position.y);
            hitbox->setRotation(c.rotation);
            hitbox->load();
            moveChild(c, g, deltaTime);
            for (unsigned int i : g.getLocalEntities(hitbox)) {
                if (g.getEntity(i).getTeamId() != teamId && hitbox->intersects(g.getEntity(i).getHitbox())) {
                    g.getEntity(i).hit(g, *this);
                }
            }
        }
    }
    time += deltaTime;
    if (gcTimer.done()) {
        gc(g);
        gcTimer.start();
    }
}
void dan::BulletType::render(Game &g, Context &ctx) {
    for (child &c : children) {
        if (!c.gc) {
            renderChild(c, g, ctx);
        }
    }
}
