#ifndef DANZUN_ABTRACTBULLETTYPE_H_INCLUDED
#define DANZUN_ABTRACTBULLETTYPE_H_INCLUDED

namespace dan {
    class Context;
    class Game;
}

namespace dan {
    class AbstractBulletType {
    public:
        virtual ~AbstractBulletType() = 0;
        virtual void gc(Game &g) = 0;
        virtual void logic(Game &g, float deltaTime, bool allied) = 0;
        virtual void render(Game &g, Context &c) = 0;
    };
}

#endif
