#include "RenderConfig.h"

#include <stdexcept>

#include "Image.h"
#include "Mesh.h"
#include "Shader.h"

dan::api::RenderConfig::RenderConfig(sol::userdata image, sol::userdata mesh, sol::userdata shader) {
    if (image.is<Image>() && mesh.is<Mesh>() && shader.is<Shader>()) {
        refs = { image, mesh, shader };
        this->img = image.as<Image>();
        this->mesh = mesh.as<Mesh>();
        this->shader = shader.as<Shader>();
    } else {
        throw std::runtime_exception("Invalid userdata types");
    }
}
void dan::api::RenderConfig::setup() {
    shader->use();
    img->bind();
}
void dan::api::RenderConfig::render() {
    mesh->render();
}

// Static members

void dan::api::RenderConfig::open(sol::state_view lua) {
    sol::usertype<RenderConfig> type = lua.new_usertype<RenderConfig>("RenderConfig", sol::constructors<Image(sol::userdata,sol::userdata,sol::userdata)>());

    // yes no?
    // type["setup"] = &RenderConfig::setup;
    // type["render"] = &RenderConfig::render;
}
