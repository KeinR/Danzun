#ifndef DANZUN_UTIL_H_INCLUDED
#define DANZUN_UTIL_H_INCLUDED

#include <string>

#include <sol/sol.hpp>

namespace dan::ut {
    /**
     * Converts an ASCII string to lowercase
     * \param in The string 
     * \return the resultant string
     * */
    std::string lowercase(const std::string &in);
    /// @{
    /**
     * Checks for an error (OpenGL or OpenAL).
     * If there is an error, will create a new err object.
     * \param sig The location of the caller
     * \param lua The lua state
     * */
    void checkGLError(const char *sig, sol::state_view lua);
    void checkALError(const char *sig, sol::state_view lua);
    /// @}
}

#endif
