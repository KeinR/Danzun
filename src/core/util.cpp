#include "util.h"

std::string dan::ut::lowercase(const std::string &in) {
    std::string result = in;
    for (char &c : result) {
        if ('A' <= c && c <= 'Z') {
            c |= 0x20;
        }
    }
    return result;
}
