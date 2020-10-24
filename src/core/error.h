#ifndef DANZUN_ERROR_H_INCLUDED
#define DANZUN_ERROR_H_INCLUDED

#include <sstream>
#include <string>

namespace eng {
    class err: public std::stringstream {
        bool severe;
        std::string location;
        void doRaise();
    public:
        err(const std::string &location, bool severe = false);
        ~err();
        static void raise(const std::string &message, bool severe);
        static const char *glErrStr(int err);
    };    
}

#endif
