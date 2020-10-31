#include "Program.h"

#include <iostream>

#include "../../src/lib/glfw.h"
#include "../../src/win/Window.h"
#include "../../src/gfs/Texture.h"
#include "../../src/ManImage.h"
#include "../../src/lib/opengl.h"

Program::Program() {
    shader = std::make_shared<dan::Shader>("data/shaders/basic.vert", "data/shaders/basic.frag");
    engine.getContext().setShader(shader);
    shader->setInt1("tex", 0);

    engine.setWindowEventCallback(this);
    engine.setEventCallback(this);
    engine.setScene(scene);

    engine.setGameSize(400, 400);

    std::shared_ptr<dan::Texture> tex = std::make_shared<dan::Texture>(dan::Texture::tparam{
        GL_CLAMP_TO_EDGE,
        GL_CLAMP_TO_EDGE,
        // GL_LINEAR_MIPMAP_LINEAR,
        // GL_LINEAR
        GL_NEAREST,
        GL_NEAREST,
    });
    tex->setImage(dan::ManImage("data/test.png"));
    // tex->genMipmap();

    dan::Sprite playerSprite;

    playerSprite.setTexture(tex);
    playerSprite.setX(50);
    playerSprite.setY(50);
    playerSprite.setWidth(200);
    playerSprite.setHeight(200);

    player = std::make_shared<dan::Player>();
    player->setSprite(playerSprite);
    player->setX(100);
    player->setY(100);
    player->setSpeed(100);

    engine.getGame().setPlayer(player);

    glfwSwapInterval(1);
}
void Program::processInput(float deltaTime) {
    bool up = engine.getWindow().keyPressed(GLFW_KEY_UP);
    bool down = engine.getWindow().keyPressed(GLFW_KEY_DOWN);
    bool left = engine.getWindow().keyPressed(GLFW_KEY_LEFT);
    bool right = engine.getWindow().keyPressed(GLFW_KEY_RIGHT);
    bool combine = (up ^ down) && (left ^ right);
    if (up) {
        player->move(engine.getGame(), dan::Player::UP, deltaTime, combine);
    }
    if (down) {
        player->move(engine.getGame(), dan::Player::DOWN, deltaTime, combine);
    }
    if (left) {
        player->move(engine.getGame(), dan::Player::LEFT, deltaTime, combine);
    }
    if (right) {
        player->move(engine.getGame(), dan::Player::RIGHT, deltaTime, combine);
    }
}
void Program::onFrame(dan::Engine &e, float deltaTime) {
    processInput(deltaTime);
}
void Program::run() {
    engine.getContext().setShader(shader);
    engine.run();
}
