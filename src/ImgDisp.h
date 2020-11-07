#ifndef DANZUN_IMGDISP_H_INCLUDED
#define DANZUN_IMGDISP_H_INCLUDED

#include <memory>

#include "AbsRenderConf.h"
#include "AbsTexture.h"
#include "Shader.h"

namespace dan {
    class ImgDisp: public AbsRenderConf {
    public:
        typedef std::shared_ptr<AbsTexture> texture_t;
        typedef std::shared_ptr<Shader> shader_t;
    private:
        texture_t texture;
        // The preferred shader, can be nullptr
        shader_t shader;
    public:
        ImgDisp(const texture_t &texture = nullptr, const shader_t &shader = nullptr);
        void setTexture(const texture_t &texture);
        void setShader(const shader_t &shader);
        texture_t &getTexture();
        shader_t &getShader();

        void setup(Context &c) override;
        void render(Context &c) override;
    };
}

#endif
