#include "Engine.h"

#include "lib/opengl.h"

dan::Engine::Engine(): window("Danzun", 500, 500, 0), rc(*this) {
    window.setEventCallback(*this);
}
void dan::Engine::run() {
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    while (!window.shouldClose()) {
        glClearColor(0.4, 0.4, 0.4, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        window.swapBuffers();

        Window::pollEvents();
    }
}
