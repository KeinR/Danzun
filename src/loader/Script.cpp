#include "Script.h"

#include <fstream>
#include <stdexcept>
#include <sstream>

dan::Script::Script(const std::string &code, const std::filesystem::path &dir):
    code(code), dir(dir)
{
}
const std::string &dan::Script::getCode() const {
    return code;
}
const std::filesystem::path &dan::Script::getDir() const {
    return dir;
}

// Static members

dan::Script dan::Script::fromFile(const std::filesystem::path &path) {
    std::ifstream file(path);
    if (!file.good()) {
        throw std::invalid_argument("Could not open file: " + path.string());
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    if (!file.good()) {
        throw std::invalid_argument("Could not read from file: " + path.string());
    }

    return Script(buffer.str(), path.parent_path());
}