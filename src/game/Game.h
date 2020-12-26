#ifndef DANZUN_GAME_H_INCLUDED
#define DANZUN_GAME_H_INCLUDED

#include <vector>
#include <map>
#include <utility>
#include <list>
#include <unordered_set>
#include <memory>

#include <sol/sol.hpp>
#include <arashpartow/exprtk.hpp>

#include "../time/Timer.h"
#include "Group.h"
#include "Entity.h"
#include "../time/Clock.h"
#include "Player.h"

namespace dan {
    class Context;
    class Engine;
}

namespace dan {
    class Game {
    public:
        typedef std::shared_ptr<Entity> entity_t;
        typedef std::vector<std::pair<entity_t, entity_t>> collisionResult_t;
        typedef std::list<entity_t> entities_t;
        typedef std::shared_ptr<Renderable> renderable_t;
        typedef std::unordered_set<Renderable*> remRenderQueue_t;
        typedef std::multimap<int, renderable_t, std::greater<int>> renderQueue_t;
    private:
        // Not used internally - exlcusively for use by
        // client applications
        Engine *engine;

        int width;
        int height;

        float gcFactor;
        float gcConstant;

        Timer gcTimer;
        Clock clock;

        Player player;

        std::map<std::string, Group> groups;

        entities_t entities;
        renderQueue_t renderQueue;
        // To prevent concurrent modification, also batch removals...
        remRenderQueue_t remRenderQueue;

        Entity::symbolTable_t globalSymbols;

        // Clean up entities
        void gc();
        entities_t::iterator eraseEntity(const entities_t::iterator &it);
    public:
        Game(Engine &e);

        Engine &getEngine() const;
        Clock &getClock();
        Player &getPlayer();
        Entity::symbolTable_t &getGlobalSymbols();

        Group &getGroup(const std::string &name);
        void clearGroups();
        void resetGroups();
        void remFromGroups(Entity *ptr);
        collisionResult_t testCollisions(const std::string &a, const std::string &b);

        void addEntity(const entity_t &e);
        void submitRenderable(int priority, const renderable_t &rend);
        void removeRenderable(Renderable *rend);

        void setWidth(int w);
        void setHeight(int h);
        void setGCFactor(float f);
        void setGCConstant(float c);

        void setGCTimeMilliseconds(unsigned int v);
        unsigned int getGCTimeMilliseconds();

        int getWidth();
        int getHeight();
        float getGCFactor();
        float getGCConstant();

        void logic(float deltaTime);
        void render(Context &c);


        static Game &fromLua(sol::state_view lua);
    };
}

#endif
