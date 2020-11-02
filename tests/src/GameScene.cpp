#include "GameScene.h"

#include <memory>

#include "../../src/gfs/Matrix.h"
#include "../../src/Engine.h"
#include "../../src/core/Context.h"
#include "../../src/game/Player.h"

GameScene::GameScene() {
}
void GameScene::render(dan::Context &c) {
    c.getEngine().renderGameTarget();
    c.getEngine().bindGameTexture();
    dan::Matrix(0, 0,
        c.getEngine().getGame().getWidth(),
        c.getEngine().getGame().getHeight()
    ).load(c);
    c.renderQuad();
    // c.getEngine().getGame().render(c);
    // c.getEngine().getGame().getPlayer()->render(c);
}
