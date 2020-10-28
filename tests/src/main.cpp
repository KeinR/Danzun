#include <iostream>

#include "../../src/Engine.h"

#include "GameScene.h"

int main() {
    dan::Engine e;
    GameScene scene;
    e.setScene(scene);
    e.run();
}
