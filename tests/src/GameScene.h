#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include "../../src/ui/Node.h"
#include "../../src/core/Context.h"
#include "../../src/sprite/Sprite.h"
#include "../../src/ui/BffFont.h"
#include "../../src/render/Shader.h"
#include "../../src/core/Context.h"
#include "../../src/sprite/Atlas.h"
#include "../../src/ani/Animation.h"

class GameScene: public dan::Node {
    dan::BffFont font;
    std::shared_ptr<dan::Shader> textShader;
    std::shared_ptr<dan::Shader> defShader;
public:
    GameScene(dan::Context &c, const std::shared_ptr<dan::Shader> &defShader);
    void render(dan::Context &c);
};

#endif
