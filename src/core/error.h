#ifndef DANZUN_ERROR_H_INCLUDED
#define DANZUN_ERROR_H_INCLUDED

#include <sstream>
#include <string>

namespace dan {
    class err: public std::stringstream {
    public:
        typedef int flag_t;
        constexpr static flag_t NONE = 0;
        // The program cannot recover and should terminate.
        // If this is set WARNING does nothing
        constexpr static flag_t SEVERE = 1 << 0;
        // If not set, assume error.
        // Does noting if SEVERE is set
        constexpr static flag_t WARNING = 1 << 1;
    private:
        std::string location;
        flag_t flags;
        bool throwOnDestruct;
        bool getFlag(flag_t f);
    public:

        err(const std::string &location, flag_t flags = NONE, bool throwOnDestruct = true);
        ~err();
        void raise();
        static const char *glErrStr(int err);
    };    
}

#endif
