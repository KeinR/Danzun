#include "Target.h"

#include "../core/Context.h"
#include "../core/debug.h"
#include "../lib/opengl.h"
#include "../ui/Node.h"

dan::Target::Target():
    result(Texture::tparam{
        GL_CLAMP_TO_EDGE,
        GL_CLAMP_TO_EDGE,
        GL_NEAREST,
        GL_NEAREST,
    }),
    node(nullptr)
{
    setSize(100, 100);
    target.attachTexture(result);
    Framebuffer::bindDefault();
}
void dan::Target::setSize(int w, int h) {
    width = w;
    height = h;
    result.setData(Texture::RGBA, width, height, NULL);
}
void dan::Target::setNode(Node &n) {
    node = &n;
}
void dan::Target::bindTexture() {
    result.bind();
}
void dan::Target::render(Context &c) {
    DANZUN_ASSERT(node != nullptr);

    target.bind();

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    c.setViewport(width, height);

    node->render(c);

    Framebuffer::bindDefault();
}
