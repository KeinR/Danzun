#ifndef DANZUN_ENTITY_H_INCLUDED
#define DANZUN_ENTITY_H_INCLUDED

namespace dan {
    class Circle;
    class Game;
    class AbstractBulletType;
}

namespace dan {
    class Entity {
    public:
        virtual ~Entity() = 0;
        virtual int getTeamID() = 0;
        virtual const Circle &getHitbox() = 0;
        virtual void hit(Game &g, AbstractBulletType &culprate) = 0;
    };
}

#endif
