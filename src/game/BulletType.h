#ifndef DANZUN_BULLETTYPE_H_INCLUDED
#define DANZUN_BULLETTYPE_H_INCLUDED

#include <vector>

#include <glm/glm.hpp>

#include "AbstractBulletType.h"
#include "../Sprite.h"
#include "../math/Hitbox.h"

namespace dan {
    class Game;
}

namespace dan {
    class BulletType: public AbstractBulletType {
    public:
        typedef std::shared_ptr<Hitbox> hitbox_t;
        struct child {
            glm::vec3 position;
            glm::vec3 velocity;
            glm::vec3 initPosition;
            float startTime;
        };
    private:
        std::vector<child> children;
        hitbox_t hitbox;
        Sprite sprite;
        float time;
    protected:
        virtual void moveChild(child &c, Game &g, float deltaTime) = 0;
        virtual void renderChild(child &c, Game &g, Context &ctx) = 0;
    public:
        BulletType();
        void setSprite(const Sprite &s);
        Sprite &getSprite();
        // Latency is the time delay, is subtracted from the current time to get the child's start time
        void addChild(const glm::vec3 &position, const glm::vec3 &velocity, float latency = 0.0f);
        void gc(Game &g);
        void logic(Game &g, float deltaTime);
        void render(Game &g, Context &ctx);
    }
}

#endif
