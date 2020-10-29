#include "GameScene.h"

#include <memory>

#include "../../src/gfs/Texture.h"
#include "../../src/ManImage.h"

GameScene::GameScene() {
    std::shared_ptr<dan::Texture> tex = std::make_shared<dan::Texture>();

    dan::ManImage img("data/test.png");
    tex->setImage(img);

    testSprite.setTexture(tex);
    testSprite.setX(50);
    testSprite.setY(50);
    testSprite.setWidth(100);
    testSprite.setHeight(100);
}
void GameScene::render(dan::Context &c) {
    testSprite.render(c);
}
