#ifndef DANZUN_GAME_H_INCLUDED
#define DANZUN_GAME_H_INCLUDED

#include <memory>
#include <vector>

#include "../Node.h"
#include "../Target.h"

#include "BulletType.h"

namespace dan {
    class Context;
}

namespace dan {
    class Game: public Node {
    public:
        typedef std::shared_ptr<BulletType> bulletType_t;
        typedef std::vector<bulletType_t> bullets_t;
    private:
        bullets_t bullets;
        int width;
        int height;
    public:
        Game();
        void setWidth(int w);
        void setHeight(int h);
        int getWidth();
        int getHeight();

        void pushBulletType(const bulletType_t &type);
        void logic(float deltaTime);
        void render(Context &c) override;
    };
}

#endif
