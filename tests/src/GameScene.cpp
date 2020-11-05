#include "GameScene.h"

#include <memory>
#include <string>

#include "../../src/gfs/Matrix.h"
#include "../../src/Engine.h"
#include "../../src/core/Context.h"
#include "../../src/game/Player.h"
#include "../../src/gfs/Color.h"

GameScene::GameScene(dan::Context &c): font("data/consolas18.bff") {
    textShader = std::make_shared<dan::Shader>("data/shaders/text.vert", "data/shaders/text.frag");
    c.setShader(textShader);
    textShader->setInt1("atlas", 0);
}
void GameScene::render(dan::Context &c) {
    c.getEngine().renderGameTarget();
    c.getEngine().bindGameTexture();
    dan::Matrix(0, 0,
        c.getEngine().getGame().getWidth(),
        c.getEngine().getGame().getHeight()
    ).load(c);
    c.renderQuad();

    const std::string text = "Some text...";

    c.setShader(textShader);
    dan::Matrix(
        300, 300,
        font.getLinesWidth(text) * 2,
        font.getLinesHeight(text) * 2
    ).load(c);
    font.bindAtlas();
    font.genMesh(text, 0xFF0000).render();
    // c.getEngine().getGame().render(c);
    // c.getEngine().getGame().getPlayer()->render(c);
}
