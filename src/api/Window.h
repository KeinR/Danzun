#ifndef DANZUN_API_WINDOW_H_INCLUDED
#define DANZUN_API_WINDOW_H_INCLUDED

#include <unordered_map>
#include <string>

#include <sol/sol.hpp>

#include "../win/enums.h"

namespace dan {
    class Window;
}

namespace dan::api {
    class Window {
        typedef std::unordered_map<std::string, dan::keyt> keyMappings_t;
        ::dan::Window *handle;
        keyMappings_t keyMappings;
        bool checkMainThread(sol::this_state l, const char *trace);
    public:
        Window(::dan::Window &handle);

        void setTitle(sol::this_state l, const std::string &text);
        void setSize(sol::this_state l, int width, int height);
        void setVisible(sol::this_state l, bool toggle);
        bool keyDown(sol::this_state l, const std::string &name);

        static void open(sol::state_view lua);
    };
}

#endif
