#ifndef DAN_API_RENDERCONFIG_H_INCLUDED
#define DAN_API_RENDERCONFIG_H_INCLUDED

#include <array>
#include <memory>

#include <sol/sol.hpp>

#include "../sprite/AbsRenderConf.h"

namespace dan {
    namespace api {
        class Image;
        class Mesh;
        class Shader;
    }
    class Context;
}

namespace dan::api {
    class RenderConfig: public AbsRenderConf {
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

        // Just call their namesakes
        void setup(Context &c) override;
        void render(Context &c) override;

        static std::shared_ptr<RenderConfig> make(sol::userdata image, sol::userdata mesh, sol::userdata shader);

        static void open(sol::state_view lua);
    };
}

#endif
