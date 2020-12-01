#include "Program.h"

#include <lua/lua.hpp>

#include <iostream>
#include "../lib/opengl.h"

#include "libs/engine.h"
#include "libs/game.h"
#include "libs/Shader.h"
#include "libs/window.h"
#include "libs/Mesh.h"
#include "libs/Image.h"

dan::Program::Program(const std::filesystem::path &startFile): engine("Danzun", 500, 500), data(engine.getContext()) {
    vm.setProgram(*this);

    std::filesystem::path p = std::filesystem::absolute("../data/lua/game.lua");
    std::filesystem::path t = std::filesystem::absolute(startFile);

    // IMPORTANT: Set working directory to that of the init script
    // so that clients can use I/O sanely
    std::filesystem::current_path(startFile.parent_path());

    t = std::filesystem::relative(t);
    vm.execFile(t.string());

    std::cout << "start open windows" << '\n';

    vm.openLib(libs::window());
    vm.openLib(libs::shader());
    vm.openLib(libs::mesh());
    vm.openLib(libs::image());

    std::cout << "libs done" << '\n';

    vm.execFile(p.string());

    std::cout << "Setup done" << '\n';

    vm.call("preInit");

    std::cout << "Pre done" << '\n';

    vm.openLib(libs::engine());

    std::cout << "Engine opened" << '\n';

    engine.getWindow().setVisible(true);

    vm.call("init");

    vm.call("start");

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glViewport(0, 0, 500, 500);

    while (true) {
        glClearColor(0, 0.4, 0.4, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        vm.call("main");
        engine.getWindow().swapBuffers();
        Window::pollEvents();
    }
}
dan::Data &dan::Program::getData() {
    return data;
}
dan::Engine &dan::Program::getEngine() {
    return engine;
}
