#ifndef DANZUN_GAME_H_INCLUDED
#define DANZUN_GAME_H_INCLUDED

#include <memory>
#include <vector>

#include "../Node.h"
#include "../Target.h"
#include "Entity.h"

#include "BulletType.h"

#include "../math/Hitbox.h"

namespace dan {
    class Context;
}

namespace dan {
    class Game: public Node {
    public:
        typedef std::shared_ptr<Hitbox> hitbox_t;
        typedef std::shared_ptr<BulletType> bulletType_t;
        typedef std::vector<bulletType_t> bullets_t;
        typedef std::shared_ptr<Entity> entity_t;
        typedef std::vector<entity_t> entities_t;
    private:
        bullets_t bullets;
        entities_t entities;
        int width;
        int height;
    public:
        Game();
        void setWidth(int w);
        void setHeight(int h);
        void addEntity(const entity_t &e);

        int getWidth();
        int getHeight();
        std::vector<unsigned int> getLocalEntities(const hitbox_t &h);
        Entity &getEntity(unsigned int index);


        void pushBulletType(const bulletType_t &type);
        void logic(float deltaTime);
        void render(Context &c) override;
    };
}

#endif
