#ifndef DAN_API_RENDERCONFIG_H_INCLUDED
#define DAN_API_RENDERCONFIG_H_INCLUDED

#include <array>

#include <sol/sol.hpp>

namespace dan {
    namespace api {
        class Image;
        class Mesh;
        class Shader;
    }
    class Context;
}

namespace dan::api {
    class RenderConfig {
        std::array<sol::userdata, 3> refs;
        Image *img;
        Mesh *mesh;
        Shader *shader;
    public:
        RenderConfig(sol::userdata image, sol::userdata mesh, sol::userdata shader);
        // Bindings
        void setup();
        // Actual rendering
        void render();

        static void open(sol::state_view lua);
    };
}

#endif
