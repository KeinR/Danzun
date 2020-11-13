#ifndef DANZUN_ABSBULLETTYPE_H_INCLUDED
#define DANZUN_ABSBULLETTYPE_H_INCLUDED

namespace dan {
    class Context;
    class Game;
}

namespace dan {
    class AbsBulletType {
    public:
        virtual ~AbsBulletType() = 0;
        virtual void gc(Game &g) = 0;
        virtual void logic(Game &g, float deltaTime, bool allied) = 0;
        virtual void renderChildren(Game &g, Context &c) = 0;
        virtual long getDamage() = 0;
    };
}

#endif
