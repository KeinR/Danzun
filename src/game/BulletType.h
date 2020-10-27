#ifndef DANZUN_BULLETTYPE_H_INCLUDED
#define DANZUN_BULLETTYPE_H_INCLUDED

#include <vector>

#include <glm/glm.hpp>

#include "AbstractBulletType.h"
#include "../Sprite.h"
#include "../math/Hitbox.h"
#include "../Timer.h"
#include "Entity.h"

namespace dan {
    class Game;
}

namespace dan {
    class BulletType: public AbstractBulletType {
    public:
        typedef std::shared_ptr<Hitbox> hitbox_t;
        struct child {
            glm::vec2 position;
            glm::vec2 velocity;
            glm::vec2 initPosition;
            // Degrees
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
        Timer gcTimer;
        float time;
        bool autoGC;
        // The team it's a part of - will hurt other team(s).
        // Defaults to 0
        int teamId;
    protected:
        virtual void moveChild(child &c, Game &g, float deltaTime) = 0;
        virtual void renderChild(child &c, Game &g, Context &ctx) = 0;
    public:
        BulletType();
        void setSprite(const Sprite &s);
        Sprite &getSprite();
        void setHitbox(const hitbox_t &hb);
        void setViewHitbox(const hitbox_t &hb);
        void setTeamID(int id);
        // Latency is the time delay, is subtracted from the current time to get the child's start time
        void addChild(const glm::vec2 &position, const glm::vec2 &velocity, float rotation = 0.0f);
        void gc(Game &g);
        void logic(Game &g, float deltaTime);
        void render(Game &g, Context &ctx);
    };
}

#endif
