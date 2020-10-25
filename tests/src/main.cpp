#include <iostream>

#include "../../src/Engine.h"

int main() {
    dan::Engine e;
    std::cout << "It doesn't crash!!" << '\n';
    e.run();
}
