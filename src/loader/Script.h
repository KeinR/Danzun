#ifndef DANZUN_SCRIPT_H_INCLUDED
#define DANZUN_SCRIPT_H_INCLUDED

#include <string>
#include <filesystem>

namespace dan {
    class Script {
        std::string code;  
        std::filesystem::path dir;
    public:
        Script(const std::string &code, const std::filesystem::path &dir);
        const std::string &getCode() const;
        const std::filesystem::path &getDir() const;
        // Throws std::invalid_argument if failed to load
        static Script fromFile(const std::filesystem::path &path);
    };
}

#endif
