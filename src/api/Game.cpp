#include "Game.h"

#include <stdexcept>

#include "../game/Game.h"
#include "RenderConfig.h"
#include "../game/LuaRef.h"
#include "PatternVars.h"
#include "../core/debug.h"


dan::api::Game::Game(::dan::Game &handle): handle(&handle) {
}

// void dan::api::Game::regCircleCol(sol::table self, const std::string &groupName, float xCenter, float yCenter, float radius) {
//     dan::Group::circle c;
//     c.obj = self;
//     c.hitbox.setX(xCenter);
//     c.hitbox.setY(yCenter);
//     c.hitbox.setRadius(radius);
//     handle->getGroup(groupName).pushCircle(c);
// }
void dan::api::Game::testCollisions(const std::string &groupA, const std::string &groupB) {
    for (std::pair<::dan::Entity*, ::dan::Entity*> &p : handle->testCollisions(groupA, groupB)) {
        p.first->getHitCallback().call(::dan::api::Entity(*p.first), ::dan::api::Entity(*p.second));
        p.second->getHitCallback().call(::dan::api::Entity(*p.second), ::dan::api::Entity(*p.first));
    }
}

dan::api::Entity dan::api::Game::spawnEntityFull(
    sol::function hitCallback, sol::userdata disp, const std::string &equation,
    sol::table vars, sol::table constants,
    float x, float y, float width, float height, bool autoGC,
    const std::string &group, int renderPriority,
    sol::object points
) {
    if (disp.is<RenderConfig>()) {
        std::vector<sol::userdata> deps;
        std::vector<PatternVars::symTable_t> tables;
        deps.reserve(vars.size());
        tables.reserve(vars.size());
        for (auto &d : vars) {
            if (d.second.is<PatternVars>()) {
                deps.push_back(d.second);
                tables.push_back(d.second.as<PatternVars>().getTable());
            }
        }

        std::vector<std::pair<std::string, float>> csts;
        for (auto p : constants) {
            if (p.first.get_type() == sol::type::string &&
                p.second.get_type() == sol::type::number)
            {
                csts.push_back({p.first.as<std::string>(), p.second.as<float>()});
            }
        }

        ::dan::Entity &e = handle->addEntity(
            hitCallback, LuaRef<RenderConfig>(disp), equation,
            tables, csts,
            x, y, width, height, autoGC
        );
        for (sol::userdata d : deps) {
            e.addReference(d);
        }

        handle->submitRenderable(renderPriority, e);

        Group &g = handle->getGroup(group);

        if (points.get_type() == sol::type::nil) {
            g.pushCircle(e);
        } else {
            DANZUN_ASSERT(false); // NOT IMPLEMENTED
        }

        return ::dan::api::Entity(e);
    } else {
        throw std::runtime_error("Expected RenderConfig as second arg");
    }
}

void dan::api::Game::resetGroups() {
    handle->resetGroups();
}
float dan::api::Game::getTime() {
    return handle->getClock().getTime();
}
float dan::api::Game::getDeltaTime() {
    return handle->getClock().getDeltaTime();
}

// Static members

void dan::api::Game::open(sol::state_view &lua) {
    sol::usertype<Game> type = lua.new_usertype<Game>("Game");

    // type["regCircleCol"] = &Game::regCircleCol;
    type["testCollisions"] = &Game::testCollisions;
    type["resetGroups"] = &Game::resetGroups;
    type["getTime"] = &Game::getTime;
    type["getDeltaTime"] = &Game::getDeltaTime;
    type["spawnEntityFull"] = &Game::spawnEntityFull;
    type["submitRenderable"] = &Game::spawnEntityFull;
    type["addCircle"] = &Game::spawnEntityFull;

}
