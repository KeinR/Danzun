#ifndef DANZUN_API_SHADER_H_INCLUDED
#define DANZUN_API_SHADER_H_INCLUDED

#include <array>
#include <memory>

#include <sol/sol.hpp>

#include "../render/Shader.h"

namespace dan::api {
    /**
     * Wrapper for the shader class
     * */
    class Shader {
        /// The shader
        std::shared_ptr<::dan::Shader> shader;
    public:
        /**
         * Construct a shader from files
         * \param l The current state
         * \param vertex The path of the vertex shader
         * \param fragment The path of the fragment shader
         * */
        Shader(sol::this_state l, const std::string &vertex, const std::string &fragment);

        /// @{
        /**
         * Set shader uniform.
         * The number of parameters for values determines the type of variable
         * (ex, setInt("foo", 4, 3) would set a vec2. Make sure that you know
         * the type of variable!)
         * Only up to 4 values, and at least 1.
         * \note The shader is bound if it wasn't before
         * \param name The uniform name
         * \param values The uniform values
         * */
        void setInt(const std::string &name, sol::variadic_args values, int);
        void setFloat(const std::string &name, sol::variadic_args values, float);

        /// @}

        /**
         * Sets a 4x4 matrix.
         * Good for when the Matrix abstraction is useless.
         * \param name The uniform name
         * \param values The matrix values
         * */
        void setMat4(const std::string &name, const std::array<float, 16> &values);

        /**
         * Binds this shader if not already bound (glUseProgram())
         * */
        void use();

        /**
         * Check if the shader is invalid
         * \return true if yes
         * */
        bool isFailed();

        /**
         * Registers this class when the given state
         * \param lua The state
         * */
        static void open(sol::state_view &lua);
    };
}

#endif
