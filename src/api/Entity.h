#ifndef DAN_API_ENTITY_H_INCLUDED
#define DAN_API_ENTITY_H_INCLUDED

#include <memory>
#include <set>
#include <string>

#include <sol/sol.hpp>

#include "RenderConfig.h"
#include "Script.h"

namespace dan {
    class Entity;
}

namespace dan::api {
    class Entity {
    public:
        typedef std::shared_ptr<::dan::Entity> handle_t;
    private:
        handle_t handle;
    public:
        Entity(const handle_t &v);
        Entity(sol::this_state l,
            sol::function hitCallback, const std::shared_ptr<RenderConfig> &disp,
            const std::string &equation, sol::variadic_args vars);

        handle_t getHandle();

        void setScript(const Script &s);

        void activate(sol::this_state l);
        void deactivate(sol::this_state l);
        void setRenderPriority(sol::this_state l, int value);

        void regCircle(sol::this_state l, const std::string &group);
        void regPolygon(sol::this_state l, const std::string &group, sol::table points);
        void unregHitboxes(sol::this_state l);

        // foo[fef]
        float index(const std::string &name);
        // foo[fef] = bar
        void newIndex(const std::string &name, float value);

        static void open(sol::state_view &lua);
    };
}

#endif
