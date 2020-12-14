#ifndef DANZUN_GAME_H_INCLUDED
#define DANZUN_GAME_H_INCLUDED

#include <vector>
#include <map>
#include <utility>
#include <list>
#include <unordered_set>
#include <functional>

#include <sol/sol.hpp>

#include <arashpartow/exprtk.h>

#include "../ui/Node.h"
#include "../time/RealTimer.h"

#include "Group.h"
#include "Bullet.h"
#include "Pattern.h"
#include "PatternInst.h"
#include "../time/Clock.h"

namespace dan {
    class Context;
    class Player;
    class Engine;
}

namespace dan {
    class Game: public Node {
    public:
        typedef std::vector<std::pair<sol::table, sol::table>> collisionResult_t;
        typedef std::list<Entity> entities_t;
        typedef std::miltimap<int, Renderable*, std::greater> renderQueue_t;
    private:
        // Not used internally - exlcusively for use by
        // client applications
        Engine *engine;

        int width;
        int height;

        RealTimer gcTimer;
        Clock clock;

        std::map<std::string, Group> groups;

        // Paths to
        std::map<std::string, std::string> stages;

        entities_t entities;
        renderQueue_t renderQueue;

        // Clean up entities
        void gc();
        entities_t::iterator deleteEntity(const entities_t::const_iterator &it);
    public:
        Game(Engine &e);

        Engine &getEngine() const;

        Group &getGroup(const std::string &name);
        void clearGroups();
        void resetGroups();
        collisionResult_t testCollisions(const std::string &a, const std::string &b);

        Entity &addEntity(sol::function hitCallback, const disp_t &disp, const std::string &equation, float x, float y, float width, float height, bool autoGC);
        // REF MUST STAY VALID
        void submitRenderable(Renderable &rend);
        void removeRenderable(Renderable *rend);

        void addStage(const std::string &name, const std::string &path);
        std::string &getStage(const std::string &name);

        void setWidth(int w);
        void setHeight(int h);

        int getWidth();
        int getHeight();

        void logic(float deltaTime);
        void runGroup(const std::string &name);
        void render(Context &c) override;
    };
}

#endif
