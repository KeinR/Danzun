#include "Program.h"

#include <iostream>

#include "../../src/lib/glfw.h"
#include "../../src/win/Window.h"
#include "../../src/gfs/Texture.h"
#include "../../src/ManImage.h"
#include "../../src/lib/opengl.h"
#include "Enemy.h"

Program::Program() {
    shader = std::make_shared<dan::Shader>("data/shaders/basic.vert", "data/shaders/basic.frag");
    engine.getContext().setShader(shader);
    shader->setInt1("tex", 0);

    engine.setWindowEventCallback(this);
    engine.setEventCallback(this);
    engine.setScene(scene);

    engine.setGameSize(400, 400);

    dan::Sprite playerSprite;

    playerSprite.setTexture(loadTex("data/player.png"));
    playerSprite.setX(50);
    playerSprite.setY(50);
    playerSprite.setWidth(50);
    playerSprite.setHeight(50);

    player = std::make_shared<dan::Player>();
    player->setSprite(playerSprite);
    player->setX(100);
    player->setY(100);
    player->setSpeed(100);

    engine.getGame().setPlayer(player);
    bullet = std::make_shared<Bullet>(loadTex("data/bullet.png"));

    engine.getGame().pushAllyBulletType(bullet);
    engine.setGameActive(true);

    glfwSwapInterval(1);

    bulletCooldown.set(0.05);

    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(loadTex("data/player.png"));
    engine.getGame().addEntity(enemy);
}

Program::tex_t Program::loadTex(const std::string &path) {
    tex_t tex = std::make_shared<dan::Texture>(dan::Texture::tparam{
        GL_CLAMP_TO_EDGE,
        GL_CLAMP_TO_EDGE,
        GL_NEAREST,
        GL_NEAREST,
    });
    tex->setImage(dan::ManImage(path));
    return tex;
}

void Program::processInput(float deltaTime) {
    dan::Window &window = engine.getWindow();
    dan::Game &game = engine.getGame();
    bool up = window.keyPressed(GLFW_KEY_UP);
    bool down = window.keyPressed(GLFW_KEY_DOWN);
    bool left = window.keyPressed(GLFW_KEY_LEFT);
    bool right = window.keyPressed(GLFW_KEY_RIGHT);
    bool combine = (up ^ down) && (left ^ right);
    bool shoot = window.keyPressed(GLFW_KEY_Z);
    if (up) {
        player->move(game, dan::Player::UP, deltaTime, combine);
    }
    if (down) {
        player->move(game, dan::Player::DOWN, deltaTime, combine);
    }
    if (left) {
        player->move(game, dan::Player::LEFT, deltaTime, combine);
    }
    if (right) {
        player->move(game, dan::Player::RIGHT, deltaTime, combine);
    }
    bulletCooldown.advance(deltaTime);
    if (shoot && bulletCooldown.done()) {
        bullet->addChild({player->getX(), player->getY()}, {0, -600});
        bulletCooldown.reset();
    }
}
void Program::onFrame(dan::Engine &e, float deltaTime) {
    processInput(deltaTime);
}
void Program::run() {
    engine.getContext().setShader(shader);
    engine.run();
}
