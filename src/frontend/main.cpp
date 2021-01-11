#include <iostream>
#include <stdexcept>

#include <adishavit/argh.h>

#include <cmake/config.h>

#include "../core/Engine.h"

static const char *const usage =
R"(Usage

    danzun [options] script

Executes a given Lua script inside the Danzun game engine.
Documentation: <https://github.com/KeinR/Danzun>

Options

    -h, --help      Prints this message and exits
    -v, --version   Prints the version and copyright information and exits

)";

static const char *const version = "Danzun " DANZUN_VERSION "\nCopyright (C) Orion \"KeinR\" Musselman under the MIT license.\n";

int main(int argc, char **argv) {

    argh::parser cmdl;
    cmdl.add_params({
        "-s", "--msaa"
    });
    cmdl.parse(argc, argv);

    if (cmdl[{"-v", "--version"}]) {
        std::cout << version;
        return 0;
    }

    if (cmdl[{"-h", "--help"}]) {
        std::cout << usage;
        return 0;
    }

    int msaa;
    cmdl({"-s", "--msaa"}, 0) >> msaa;

    if (cmdl.size() < 2) {
        std::cerr << "Must provide path to game script" << '\n';
        return 1;
    }

    std::string script = cmdl[cmdl.size() - 1];

    try {
        dan::Engine e(msaa);
        e.start(script);
    } catch (std::exception &e) {
        std::cerr << "Err - terminated: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
