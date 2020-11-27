#include "Program.h"

dan::Program::Program(const Script &init): engine("Danzun", 500, 500) {
    vm.exec(init);
}
dan::Data &dan::Program::getData() {
    return data;
}
dan::Engine &dan::Program::getEngine() {
    return engine;
}
