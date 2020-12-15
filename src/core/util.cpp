#include "util.h"

std::string dan::ut::dirname(const std::string &path) {
    for (std::string::size_type i = path.size() - 1; i < path.size(); i--) {
        if (path[i] == '/') {
            std::string result = path;
            if (i + 1 < result.size()) {
                result.erase(i + 1);
            }
            return result;
        }
    }
    // Must be in the base dir 
    return "";
}

std::string dan::ut::lowercase(const std::string &in) {
    std::string result = in;
    for (char &c : result) {
        if ('A' <= c && c <= 'Z') {
            c |= 0x20;
        }
    }
    return result;
}
