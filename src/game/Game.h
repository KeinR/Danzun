#ifndef DANZUN_GAME_H_INCLUDED
#define DANZUN_GAME_H_INCLUDED

#include <vector>
#include <map>
#include <utility>
#include <list>
#include <unordered_set>
#include <functional>
#include <memory>

#include <sol/sol.hpp>

#include <arashpartow/exprtk.hpp>

#include "../win/WindowEvent.h"

#include "../time/RealTimer.h"

#include "Group.h"
#include "Entity.h"
#include "../time/Clock.h"
#include "../api/RenderConfig.h"
#include "Player.h"

namespace dan {
    class Context;
    class Player;
    class Engine;
}

namespace dan {
    class Game {
    public:
        typedef std::shared_ptr<Entity> entity_t;
        typedef std::vector<std::pair<entity_t, entity_t>> collisionResult_t;
        typedef std::list<entity_t> entities_t;
        typedef std::weak_ptr<Renderable> renderable_t;
        typedef std::shared_ptr<Renderable> renderableLock_t;
        typedef std::multimap<int, renderable_t, std::greater<int>> renderQueue_t;
    private:
        // Not used internally - exlcusively for use by
        // client applications
        Engine *engine;

        int width;
        int height;

        RealTimer gcTimer;
        Clock clock;

        Player player;

        std::map<std::string, Group> groups;

        entities_t entities;
        renderQueue_t renderQueue;

        Entity::symbolTable_t globalSymbols;

        // Clean up entities
        void gc();
    public:
        Game(Engine &e);

        Engine &getEngine() const;
        Clock &getClock();
        Player &getPlayer();
        Entity::symbolTable_t &getGlobalSymbols();

        Group &getGroup(const std::string &name);
        void clearGroups();
        void resetGroups();
        collisionResult_t testCollisions(const std::string &a, const std::string &b);

        entity_t addEntity(
            sol::function hitCallback, const Entity::disp_t &disp, const std::string &equation,
            const std::vector<Entity::symbolTable_t> &symbols, const Entity::constants_t &constants,
            float x, float y, float width, float height, bool autoGC
        );
        void submitRenderable(int priority, const renderable_t &rend);
        void removeRenderable(Renderable *rend);

        void setWidth(int w);
        void setHeight(int h);

        int getWidth();
        int getHeight();

        void logic(float deltaTime);
        void render(Context &c);


        static Game &fromLua(sol::state_view lua);
    };
}

#endif
