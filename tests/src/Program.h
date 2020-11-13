#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <memory>
#include <string>

#include "../../src/core/Engine.h"
#include "../../src/render/Shader.h"
#include "../../src/game/Player.h"
#include "../../src/core/EventCallback.h"
#include "../../src/time/Timer.h"
#include "../../src/render/Texture.h"
#include "../../src/win/WindowEvent.h"
#include "../../src/ani/Animation.h"
#include "../../src/ani/AniControl.h"

#include "Bullet.h"
#include "GameScene.h"

class Program: private dan::WindowEvent, private dan::EventCallback {
    typedef std::shared_ptr<dan::Texture> tex_t;

    dan::Engine engine;
    std::shared_ptr<dan::Shader> shader;
    std::shared_ptr<dan::Player> player;
    GameScene scene;
    std::shared_ptr<Bullet> bullet;
    dan::Timer bulletCooldown;
    dan::Timer enemyCooldown;

    tex_t enemyTex;

    dan::AniControl aniControl;
    dan::Animation ani;

    tex_t loadTex(const std::string &path);

    void processInput(float deltaTime);
public:
    Program();
    void onFrame(dan::Engine &e, float deltaTime) override;
    void run();
};

#endif
