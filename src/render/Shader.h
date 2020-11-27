#ifndef DANZUN_SHADER_H_INCLUDED
#define DANZUN_SHADER_H_INCLUDED

#include <string>
#include <map>

namespace dan {
    class Context;
}

namespace dan {
    class Shader {
    public:
        typedef int uniform_t;
        typedef unsigned int program_t;
    private:
        typedef std::map<std::string, uniform_t> uniforms_t;

        Context *c;
        program_t handle;
        uniforms_t uniforms;

        void free();
        void steal(Shader &other);
        uniform_t uni(const std::string &name);
        void createShader(const char *vertexData, unsigned int vertexLength, const char *fragmentData, unsigned int fragmentLength);

        uniform_t getUniform(const std::string &name);
    public:
        Shader(Context &c, const char *vertexData, unsigned int vertexLength, const char *fragmentData, unsigned int fragmentLength);
        Shader(Context &c, const std::string &vertexPath, const std::string &fragmentPath);
        Shader(Shader &&other);
        virtual ~Shader();
        Shader &operator=(Shader &&other);

        void doUse() const;
        void use();
        static void disuse();

        program_t getHandle() const;

        // NB: Binds this shader
        void setMatrix4fv(const std::string &name, const float *data);
        void setInt1(const std::string &name, int value);
        void set4fv(const std::string &name, const float *values);
    };
}

#endif
