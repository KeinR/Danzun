#include "RenderConfig.h"

#include <stdexcept>

#include "Image.h"
#include "Mesh.h"
#include "Shader.h"

dan::api::RenderConfig::RenderConfig(sol::userdata image, sol::userdata mesh, sol::userdata shader) {
    if (image.is<Image>() && mesh.is<Mesh>() && shader.is<Shader>()) {
        refs = { image, mesh, shader };
        this->img = image.as<Image*>();
        this->mesh = mesh.as<Mesh*>();
        this->shader = shader.as<Shader*>();
    } else {
        throw std::runtime_error("Invalid userdata types");
    }
}
void dan::api::RenderConfig::setup() {
    shader->use();
    img->bind();
}
void dan::api::RenderConfig::render() {
    mesh->render();
}

void dan::api::RenderConfig::setup(Context &c) {
    setup();
}
void dan::api::RenderConfig::render(Context &c) {
    render();
}

// Static members

std::shared_ptr<dan::api::RenderConfig> dan::api::RenderConfig::make(sol::userdata image, sol::userdata mesh, sol::userdata shader) {
    return std::make_shared<RenderConfig>(image, mesh, shader);
}

void dan::api::RenderConfig::open(sol::state_view lua) {
    sol::usertype<RenderConfig> type = lua.new_usertype<RenderConfig>("RenderConfig");

    type[sol::meta_function::construct] = &RenderConfig::make;

    // yes no?
    type["setup"] = static_cast<void (dan::api::RenderConfig::*)()>(&RenderConfig::setup);
    type["render"] = static_cast<void (dan::api::RenderConfig::*)()>(&RenderConfig::render);
}
