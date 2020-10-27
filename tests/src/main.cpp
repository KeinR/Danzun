#include <iostream>

#include "../../src/Engine.h"

#include "GameScene.h"

int main() {
    dan::Engine e;
    GameScene scene;
    e.setScene(scene);
    std::cout << "It doesn't crash!!" << '\n';
    e.run();
}
