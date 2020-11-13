#ifndef DANZUN_ENTITY_H_INCLUDED
#define DANZUN_ENTITY_H_INCLUDED

namespace dan {
    class Circle;
    class Game;
    class AbsBulletType;
    class Context;
}

namespace dan {
    class Entity {
    public:
        virtual ~Entity() = 0;
        virtual const Circle &getHitbox() = 0;
        virtual void logic(Game &g, float deltaTime) = 0;
        virtual void hit(Game &g, AbsBulletType &culprate) = 0;
        virtual bool shouldDelete() = 0;
        virtual void render(Context &c) = 0;
    };
}

#endif
