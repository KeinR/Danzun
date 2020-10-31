#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include "../../src/Node.h"
#include "../../src/core/Context.h"
#include "../../src/Sprite.h"

class GameScene: public dan::Node {
public:
    GameScene();
    void render(dan::Context &c);
};

#endif
