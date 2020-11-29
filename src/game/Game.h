#ifndef DANZUN_GAME_H_INCLUDED
#define DANZUN_GAME_H_INCLUDED

#include <vector>
#include <map>
#include <utility>

#include "../ui/Node.h"
#include "../time/RealTimer.h"

#include "Group.h"

namespace dan {
    class Context;
    class Player;
    class Engine;
}

namespace dan {
    class Game: public Node {
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

        // Clean up entities
        void gc();
    public:
        Game(Engine &e);

        Engine &getEngine() const;

        Group &getGroup(const std::string &name);
        void clearGroups();
        void resetGroups();
        std::vector<std::pair<int,int>> testCollisions(const std::string &a, const std::string &b);

        void addStage(const std::string &name, const std::string &path);
        std::string &getStage(const std::string &name);

        void setWidth(int w);
        void setHeight(int h);

        int getWidth();
        int getHeight();

        void logic(float deltaTime);
        void render(Context &c) override;
    };
}

#endif
