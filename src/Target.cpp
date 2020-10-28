#include "Target.h"

#include "core/debug.h"
#include "lib/opengl.h"

#include "Node.h"

dan::Target::Target():
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
    glViewport(0, 0, width, height);

    node->render(c);

    Framebuffer::bindDefault();
}
