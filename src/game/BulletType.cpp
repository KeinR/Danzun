#include "BulletType.h"

#include "../lib/glfw.h"

dan::BulletType::BulletType():
    // Run GC every ~100 ms
    gcTimer(100),
    time(0.0f),
    autoGC(true)
{
}

void dan::BulletType::setSprite(const Sprite &s) {
    sprite = s;
}
dan::Sprite &dan::BulletType::getSprite() {
    return sprite;
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
                (viewHitbox->getMinX() > game.getWidth() && it->velocity.x >= 0) ||
                (viewHitbox->getMaxY() < 0 && it->velocity.y <= 0) ||
                (viewHitbox->getMinY() > game.getHeight() >= 0 && it->velocity.y >= 0)
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
        if (!chl.gc) {
            moveChild(c, g, deltaTime);
        }
    }
    time += deltaTime;
    if (gcTimer.done()) {
        gc();
        gcTimer.start();
    }
}
void dan::BulletType::render(Game &g, Context &ctx) {
    for (child &chl : children) {
        if (!chl.gc) {
            renderChild(c, g, ctx);
        }
    }
}
