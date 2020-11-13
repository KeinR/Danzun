#ifndef DANZUN_TARGET_H_INCLUDED
#define DANZUN_TARGET_H_INCLUDED

#include "Framebuffer.h"
#include "Texture.h"

namespace dan {
    class Context;
    class Node;
}

namespace dan {
    class Target {
        Framebuffer target;
        Texture result;
        int width;
        int height;
        Node *node;
    public:
        Target();
        void setSize(int w, int h);
        void setNode(Node &n);
        void bindTexture();
        void render(Context &c);
    };
}

#endif
