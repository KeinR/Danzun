#include "Program.h"

#include <iostream>

#include "../../src/lib/glfw.h"
#include "../../src/win/Window.h"
#include "../../src/render/Texture.h"
#include "../../src/sprite/ManImage.h"
#include "../../src/sprite/ImgDisp.h"
#include "../../src/lib/opengl.h"
#include "../../src/sprite/Atlas.h"
#include "Enemy.h"

Program::Program():
    engine("Danzun test", 500, 500),
    shader(std::make_shared<dan::Shader>("data/shaders/basic.vert", "data/shaders/basic.frag")),
    scene(engine.getContext(), shader),
    bulletCooldown(engine.getContext().getClock()),
    enemyCooldown(engine.getContext().getClock())
{
    // shader = std::make_shared<dan::Shader>("data/shaders/basic.vert", "data/shaders/basic.frag");
    engine.getContext().setShader(shader);
    shader->setInt1("tex", 0);

    engine.setWindowEventCallback(this);
    engine.setEventCallback(this);
    engine.setScene(scene);

    engine.setGameSize(400, 400);

    dan::Sprite playerSprite;

    // playerSprite.setConf(std::make_shared<dan::ImgDisp>(loadTex("data/player.png")));
    playerSprite.setX(50);
    playerSprite.setY(50);
    playerSprite.setWidth(50);
    playerSprite.setHeight(50);

    player = std::make_shared<dan::Player>();
    // player->setSprite(playerSprite);
    player->setX(100);
    player->setY(100);
    player->setSpeed(100);

    engine.getGame().setPlayer(player);
    bullet = std::make_shared<Bullet>(loadTex("data/bullet.png"));

    engine.getGame().pushAllyBulletType(bullet);
    engine.setGameActive(true);

    glfwSwapInterval(1);

    bulletCooldown.set(0.05);
    enemyCooldown.set(1);

    enemyTex = loadTex("data/player.png");

    engine.getGame().addEntity(std::make_shared<Enemy>(enemyTex));

    ani = dan::Atlas::loadAnimation("data/bow-animation.json");

    playerSprite.setConf(aniControl.add(ani));
    player->setSprite(playerSprite);
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
    if (shoot && bulletCooldown.done()) {
        bullet->spawn({player->getX(), player->getY()}, {0, -100});
        bullet->spawn({player->getX(), player->getY()}, {-100, 0});
        bullet->spawn({player->getX(), player->getY()}, {0, 100});
        bullet->spawn({player->getX(), player->getY()}, {100, 0});
        bulletCooldown.reset();
    }
    // enemyCooldown.advance(deltaTime);
    // if (enemyCooldown.done()) {
    //     engine.getGame().addEntity(std::make_shared<Enemy>(enemyTex));
    //     enemyCooldown.reset();
    // }
}
void Program::onFrame(dan::Engine &e, float deltaTime) {
    processInput(deltaTime);
    aniControl.advance(deltaTime);
}
void Program::run() {
    engine.getContext().setShader(shader);
    engine.run();
}
