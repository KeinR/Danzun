#include "BulletType.h"

#include "../lib/glfw.h"

dan::BulletType::BulletType(): time(0.0f) {
}

void dan::BulletType::setSprite(const Sprite &s) {
    sprite = s;
}
dan::Sprite &dan::BulletType::getSprite() {
    return sprite;
}

void dan::BulletType::addChild(const glm::vec3 &position, const glm::vec3 &velocity) {
    children.push_back(child{
        position,
        velocity,
        position,
        time
    });
}
void dan::BulletType::gc(Game &g) {
    // ... remove bullets that have left the area ...
}
void dan::BulletType::logic(Game &g, float deltaTime) {
    for (child &c : children) {
        moveChild(c, g, deltaTime);
    }
    time += deltaTime;
}
void dan::BulletType::render(Game &g, Context &ctx) {
    for (child &chl : children) {
        renderChild(c, g, ctx);
    }
}
