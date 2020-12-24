#include <iostream>
#include <stdexcept>

#include "../core/Engine.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Must provide path to game script" << '\n';
        return 1;
    }

    try {
        dan::Engine e;
        e.start(argv[1]);
    } catch (std::exception &e) {
        std::cerr << "Err - terminated: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
