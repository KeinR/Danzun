#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include "../../src/Node.h"
#include "../../src/core/Context.h"
#include "../../src/Sprite.h"
#include "../../src/BffFont.h"
#include "../../src/Shader.h"
#include "../../src/core/Context.h"
#include "../../src/Animation.h"
#include "../../src/Atlas.h"

class GameScene: public dan::Node {
    dan::BffFont font;
    std::shared_ptr<dan::Shader> textShader;
    std::shared_ptr<dan::Shader> defShader;
    dan::Atlas atlas;
    dan::Animation ani;
    dan::Animation::Instance inst;
public:
    GameScene(dan::Context &c, const std::shared_ptr<dan::Shader> &defShader);
    void render(dan::Context &c);
};

#endif
