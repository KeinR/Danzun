#include <iostream>

#include "../../src/Engine.h"
#include "../../src/Shader.h"

#include "GameScene.h"

int main() {
    dan::Engine e;

    dan::Shader shader("data/shaders/basic.vert", "data/shaders/basic.frag");
    shader.setInt1(e.getContext(), "tex", 0);
    shader.use();

    GameScene scene;
    e.setScene(scene);
    e.run();
}
