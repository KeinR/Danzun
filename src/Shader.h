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

        program_t handle;
        uniforms_t uniforms;

        void free();
        void steal(Shader &other);
        uniform_t uni(const std::string &name);
        void createShader(const char *vertexData, unsigned int vertexLength, const char *fragmentData, unsigned int fragmentLength);

        uniform_t getUniform(const std::string &name);
    public:
        Shader(const char *vertexData, unsigned int vertexLength, const char *fragmentData, unsigned int fragmentLength);
        Shader(const std::string &vertexPath, const std::string &fragmentPath);
        Shader(Shader &&other);
        virtual ~Shader();
        Shader &operator=(Shader &&other);

        void use() const;
        static void disuse();

        program_t getHandle() const;

        void setMatrix4fv(Context &c, const std::string &name, const float *data);
        void setInt1(Context &c, const std::string &name, int value);
        void set4fv(Context &c, const std::string &name, const float *values);
    };
}

#endif
