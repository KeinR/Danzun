#include "manifest.h"

#include "Engine.h"
#include "Game.h"
#include "Shader.h"
#include "Window.h"
#include "Mesh.h"
#include "Image.h"
#include "Matrix.h"
#include "Entity.h"
#include "PatternVars.h"
#include "Script.h"
#include "Player.h"
#include "Effect.h"
#include "Pattern.h"
#include "BffFont.h"
#include "Element.h"
#include "util.h"
#include "SpeakerConf.h"

void dan::api::manifest::openAll(sol::state_view lua) {
    ::dan::api::Engine::open(lua);
    ::dan::api::Shader::open(lua);
    ::dan::api::Mesh::open(lua);
    ::dan::api::Image::open(lua);
    ::dan::api::Game::open(lua);
    ::dan::api::Window::open(lua);
    ::dan::api::Matrix::open(lua);
    ::dan::api::PatternVars::open(lua);
    ::dan::api::Entity::open(lua);
    ::dan::api::Script::open(lua);
    ::dan::api::Player::open(lua);
    ::dan::api::Effect::open(lua);
    ::dan::api::Pattern::open(lua);
    ::dan::api::BffFont::open(lua);
    ::dan::api::Element::open(lua);
    ::dan::api::util::open(lua);
    ::dan::api::SpeakerConf::open(lua);
}
