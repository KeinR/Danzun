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
#include "Effect.h"

namespace dan {
    class Context;
    class Player;
    class Engine;
}

namespace dan {
    class Game {
    public:
        typedef std::vector<std::pair<Entity*, Entity*>> collisionResult_t;
        typedef std::list<Entity> entities_t;
        typedef std::multimap<int, Renderable*, std::greater<int>> renderQueue_t;
        typedef std::vector<std::pair<std::weak_ptr<Effect>, Renderable*>> effects_t;
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

        // Paths to
        std::map<std::string, std::string> stages;

        entities_t entities;
        effects_t effects;
        renderQueue_t renderQueue;

        Entity::symbolTable_t globalSymbols;

        // Clean up entities
        void gc();
        entities_t::iterator deleteEntity(const entities_t::iterator &it);
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

        Entity &addEntity(
            sol::function hitCallback, const Entity::disp_t &disp, const std::string &equation,
            const std::vector<Entity::symbolTable_t> &symbols, const Entity::constants_t &constants,
            float x, float y, float width, float height, bool autoGC
        );
        // REF MUST STAY VALID
        void submitRenderable(int priority, Renderable &rend);
        void removeRenderable(Renderable *rend);

        void addEffect(const std::weak_ptr<Effect> &e, int renderPriority);

        void addStage(const std::string &name, const std::string &path);
        std::string &getStage(const std::string &name);

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
