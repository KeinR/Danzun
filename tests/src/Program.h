#ifndef PROGRAM_H_INCLUDED
#define PROGRAM_H_INCLUDED

#include <memory>

#include "../../src/Engine.h"
#include "../../src/Shader.h"
#include "../../src/game/Player.h"
#include "../../src/EventCallback.h"
#include "../../src/Timer.h"
#include "../../src/win/WindowEvent.h"

#include "Bullet.h"
#include "GameScene.h"

class Program: private dan::WindowEvent, private dan::EventCallback {
    dan::Engine engine;
    GameScene scene;
    std::shared_ptr<dan::Shader> shader;
    std::shared_ptr<dan::Player> player;
    std::shared_ptr<Bullet> bullet;
    dan::Timer bulletCooldown;
    void processInput(float deltaTime);
public:
    Program();
    void onFrame(dan::Engine &e, float deltaTime) override;
    void run();
};

#endif
