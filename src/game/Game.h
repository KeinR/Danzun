#ifndef DANZUN_GAME_H_INCLUDED
#define DANZUN_GAME_H_INCLUDED

#include <memory>
#include <vector>

#include "../Node.h"
#include "../Target.h"
#include "Entity.h"

#include "AbstractBulletType.h"

#include "../math/Hitbox.h"

namespace dan {
    class Context;
    class Player;
}

namespace dan {
    class Game: public Node {
    public:
        typedef std::shared_ptr<Hitbox> hitbox_t;
        typedef std::shared_ptr<AbstractBulletType> bulletType_t;
        typedef std::vector<bulletType_t> bullets_t;
        typedef std::shared_ptr<Entity> entity_t;
        typedef std::vector<entity_t> entities_t;
        typedef std::shared_ptr<Player> player_t;
    private:
        bullets_t enemyBullets;
        bullets_t allyBullets;
        entities_t entities;
        int width;
        int height;
        player_t player;
    public:
        Game();

        void setWidth(int w);
        void setHeight(int h);
        void addEntity(const entity_t &e);
        void setPlayer(const player_t &p);
        player_t getPlayer() const;

        int getWidth();
        int getHeight();
        std::vector<unsigned int> getLocalEntities(const hitbox_t &h, bool allied);
        Entity &getEntity(unsigned int index);

        void pushEnemyBulletType(const bulletType_t &type);
        void pushAllyBulletType(const bulletType_t &type);
        void logic(float deltaTime);
        void render(Context &c) override;
    };
}

#endif
