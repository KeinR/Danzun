#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include "../../src/Node.h"
#include "../../src/core/Context.h"
#include "../../src/Sprite.h"
#include "../../src/BffFont.h"
#include "../../src/Shader.h"
#include "../../src/core/Context.h"

class GameScene: public dan::Node {
    dan::BffFont font;
    std::shared_ptr<dan::Shader> textShader;
    std::shared_ptr<dan::Shader> defShader;
public:
    GameScene(dan::Context &c, const std::shared_ptr<dan::Shader> &defShader);
    void render(dan::Context &c);
};

#endif
