#ifndef DANZUN_GAME_H_INCLUDED
#define DANZUN_GAME_H_INCLUDED

#include <vector>
#include <map>
#include <utility>

#include "../ui/Node.h"
#include "../time/RealTimer.h"

#include "Group.h"

#include "Pattern.h"
#include "PatternInst.h"

namespace dan {
    class Context;
    class Player;
    class Engine;
}

namespace dan {
    class Game: public Node {
    public:
        typedef std::vector<std::pair<sol::table, sol::table>> collisionResult_t;
    private:
        // Not used internally - exlcusively for use by
        // client applications
        Engine *engine;

        int width;
        int height;

        RealTimer gcTimer;
        // If entities that are below the lower
        // corner of the screen are automatically
        // deleted
        bool autoGC;

        std::map<std::string, Group> groups;

        // Paths to
        std::map<std::string, std::string> stages;

        std::map<std::string, Pattern> patterns;
        std::map<int, PatternInst> patternInstances;
        int patternInstancesId;

        // Clean up entities
        void gc();
    public:
        Game(Engine &e);

        Engine &getEngine() const;

        Group &getGroup(const std::string &name);
        void clearGroups();
        void resetGroups();
        collisionResult_t testCollisions(const std::string &a, const std::string &b);

        void addStage(const std::string &name, const std::string &path);
        std::string &getStage(const std::string &name);

        void addPattern(const std::string &name, const Pattern &p);
        int newPatternInst(const std::string &name);
        PatternInst &getPatternInst(int id);
        void deletePatternInst(int id);

        void setWidth(int w);
        void setHeight(int h);

        int getWidth();
        int getHeight();

        void logic(float deltaTime);
        void render(Context &c) override;
    };
}

#endif
