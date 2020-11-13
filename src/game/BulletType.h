#ifndef DANZUN_BULLETTYPE_H_INCLUDED
#define DANZUN_BULLETTYPE_H_INCLUDED

#include <vector>

#include <glm/glm.hpp>

#include "AbsBulletType.h"
#include "Entity.h"

#include "../sprite/Sprite.h"
#include "../math/Hitbox.h"
#include "../time/RealTimer.h"

namespace dan {
    class Game;
}

namespace dan {
    class BulletType: public AbsBulletType {
    public:
        typedef std::shared_ptr<Hitbox> hitbox_t;
        struct child {
            glm::vec2 position;
            glm::vec2 velocity;
            glm::vec2 initPosition;
            // Radians
            float rotation;
            float startTime;
            bool gc;
        };
        typedef std::vector<child> children_t;
    private:
        children_t children;
        hitbox_t hitbox;
        hitbox_t viewHitbox;
        Sprite sprite;
        RealTimer gcTimer;
        float time;
        bool autoGC;
    protected:
        virtual void move(child &c, Game &g, float deltaTime) = 0;
        virtual void render(child &c, Game &g, Context &ctx) = 0;
        // Return true to delete on hit
        virtual bool hit(child &c, Game &g, float deltaTime, bool allied);
    public:
        BulletType();
        virtual ~BulletType() = 0;

        void setSprite(const Sprite &s);
        Sprite &getSprite();
        void setHitbox(const hitbox_t &hb);
        void setViewHitbox(const hitbox_t &hb);
        // Latency is the time delay, is subtracted from the current time to get the child's start time
        void spawn(const glm::vec2 &position, const glm::vec2 &velocity, float rotation = 0.0f);
        void gc(Game &g);
        void logic(Game &g, float deltaTime, bool allied);
        void renderChildren(Game &g, Context &ctx);

        virtual long getDamage() = 0;
    };
}

#endif
