#include "GameScene.h"

#include <memory>
#include <string>
#include <iostream>

#include "../../src/render/Matrix.h"
#include "../../src/core/Engine.h"
#include "../../src/core/Context.h"
#include "../../src/game/Player.h"
#include "../../src/render/Color.h"
#include "../../src/sprite/IndexedTex.h"

GameScene::GameScene(dan::Context &c, const std::shared_ptr<dan::Shader> &defShader):
    font("data/consolas18.bff"), defShader(defShader)
{
    textShader = std::make_shared<dan::Shader>("data/shaders/text.vert", "data/shaders/text.frag");
    c.setShader(textShader);
    textShader->setInt1("atlas", 0);
    // atlas.loadAse("data/bow-animation.json");
    // for (int i = 0; i < 9; i++) {
    //     ani.pushFrame(dan::Frame(
    //         std::make_shared<dan::IndexedTex>(
    //             atlas.getFrame(i).coords,
    //             atlas.getTexture()
    //         ),
    //         atlas.getFrame(i).duration
    //     ));
    //     // std::cout << "atlas.getFrame(i).duration = " << atlas.getFrame(i).duration << '\n';
    //     // std::cout << "atlas.getFrame(i).width = " << atlas.getFrame(i).width << '\n';
    //     // std::cout << "atlas.getFrame(i).height = " << atlas.getFrame(i).height << '\n';
    // }

    // inst = ani.newInstance();
}
void GameScene::render(dan::Context &c) {
    c.setShader(defShader);
    c.getEngine().renderGameTarget();
    c.setShader(defShader);
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

    // c.setShader(defShader);
    // c.getEngine().getGame().render(c);
    // c.getEngine().getGame().getPlayer()->render(c);

    // inst.setup(c);
    // dan::Matrix(
    //     50, 50,
    //     100, 100
    // ).load(c);
    // inst.render(c);

    // atlas.getTexture()->bind();
    // c.renderQuad();
}
