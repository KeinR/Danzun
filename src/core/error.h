#ifndef DANZUN_ERROR_H_INCLUDED
#define DANZUN_ERROR_H_INCLUDED

#include <sstream>
#include <string>

#include <sol/sol.hpp>

namespace dan {
    class err: public std::stringstream {
    public:
        /// The flag type
        typedef int flag_t;
        /// No flags
        constexpr static flag_t NONE = 0;
        /// The program cannot recover and should terminate.
        /// If this is set WARNING does nothing
        constexpr static flag_t SEVERE = 1 << 0;
        /// If not set, assume error.
        /// Does nothing if SEVERE is set
        constexpr static flag_t WARNING = 1 << 1;
        /// Do NOT throw the error on destruction
        constexpr static flag_t NOTHROW = 1 << 2;

        enum class throwConf {
            /// Never throw exceptions
            NEVER,
            /// Only throw if severe
            SEVERE,
            /// Always throw exceptions
            ALL
        };

    private:
        /// The location (in native code)
        std::string location;
        /// The Lua stack trace
        std::string stackTrace;
        /// Flags
        flag_t flags;
        /// The global throw configuration
        static throwConf throwConfig;
        /**
         * Check if a flag is set
         * \return true if yes
         * */
        bool getFlag(flag_t f);
        /**
         * Construct an error with optional trace
         * \param location The C++ function the error was raised in
         * \param lua The lua state, or nullptr if this happened outside
         * \param flags Flags
         * */
        err(const std::string &location, sol::state_view *lua, flag_t flags = NONE);
    public:

        /**
         * Construct a error with a lua stack trace
         * */
        err(const std::string &location, sol::state_view lua, flag_t flags = NONE);
        /**
         * Construct an error without a stack trace
         * */
        err(const std::string &location, flag_t flags = NONE);
        /**
         * Unless the NOTHROW flag is set, will call raise()
         * */
        ~err();

        /**
         * Will either throw or log the error, depending on the global throwConfig
         * */
        void raise();
        /**
         * Stringify an OpenGL error
         * \param err The error
         * \return The string (literal)
         * */
        static const char *glErrStr(int err);
        /**
         * Stringify an OpenAL error
         * \param err The error
         * \return The string (literal)
         * */
        static const char *alErrStr(int err);
        /**
         * Get a stack trace
         * \param lua The state to get the trace from
         * \return The stack trace
         * */
        static std::string trace(sol::state_view lua);
        /**
         * Set throw policy
         * \param c The new policy
         * */
        static void setThrowConfig(throwConf c);
    };    
}

#endif
