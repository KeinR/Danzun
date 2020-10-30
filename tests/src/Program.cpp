#include "Program.h"

#include "../../src/lib/glfw.h"
#include "../../src/win/Window.h"

Program::Program() {
    shader = std::make_shared<dan::Shader>("data/shaders/basic.vert", "data/shaders/basic.frag");
    engine.getContext().setShader(shader);
    shader->setInt1("tex", 0);

    engine.setWindowEventCallback(this);
    engine.setScene(scene);
}
void Program::processInput(float deltaTime) {
    if (engine.getWindow().keyPressed(GLFW_KEY_UP)) {
        player.move(engine.getGame(), dan::Player::UP, deltaTime, false);
    }
}
void Program::onFrame(dan::Engine &e, float deltaTime) {
    processInput(deltaTime);
}
void Program::run() {
    engine.getContext().setShader(shader);
    engine.run();
}
