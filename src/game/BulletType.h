#ifndef DANZUN_BULLETTYPE_H_INCLUDED
#define DANZUN_BULLETTYPE_H_INCLUDED

namespace dan {
    class Context;
    class Game;
}

namespace dan {
    class BulletType {
    public:
        virtual ~BulletType() = 0;
        virtual void logic(Game &g, float deltaTime) = 0;
        virtual void render(Game &g, Context &c) = 0;
    };
}

#endif
