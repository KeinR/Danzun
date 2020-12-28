#include "signature.h"

#include <fstream>
#include <exception>

dan::audio::type dan::audio::getType(const std::string &path) {
    std::ifstream file;
    file.exceptions(std::ifstream::badbit | std::ifstream::failbit | std::ifstream::eofbit);
    try {
        file.open(path);
        std::string sig = "....";
        file.read(sig.data(), sig.size());
        if (sig == "RIFF") {
            return type::WAV;
        } else if (sig == "OggS") {
            return type::OGG;
        }
    } catch (std::exception &e) {
        // return type::NONE;
    }
    return type::NONE;
}
