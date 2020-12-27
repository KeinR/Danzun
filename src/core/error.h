#ifndef DANZUN_ERROR_H_INCLUDED
#define DANZUN_ERROR_H_INCLUDED

#include <sstream>
#include <string>

#include <sol/sol.hpp>

namespace dan {
    class err: public std::stringstream {
    public:
        typedef int flag_t;
        constexpr static flag_t NONE = 0;
        // The program cannot recover and should terminate.
        // If this is set WARNING does nothing
        constexpr static flag_t SEVERE = 1 << 0;
        // If not set, assume error.
        // Does nothing if SEVERE is set
        constexpr static flag_t WARNING = 1 << 1;
        // Do NOT throw the error on destruction
        constexpr static flag_t NOTHROW = 1 << 2;

        enum class throwConf {
            NEVER,
            SEVERE,
            ALL
        };

    private:
        std::string location;
        std::string stackTrace;
        flag_t flags;
        static throwConf throwConfig;
        bool getFlag(flag_t f);
        err(const std::string &location, sol::state_view *lua, flag_t flags = NONE);
    public:

        err(const std::string &location, sol::state_view lua, flag_t flags = NONE);
        err(const std::string &location, flag_t flags = NONE);
        ~err();

        void raise();
        static const char *glErrStr(int err);
        static std::string trace(sol::state_view lua);
        static void setThrowConfig(throwConf c);
    };    
}

#endif
