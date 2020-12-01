#ifndef DANZUN_IMGDISP_H_INCLUDED
#define DANZUN_IMGDISP_H_INCLUDED

#include <memory>

#include "AbsRenderConf.h"
#include "AbsTexture.h"

#include "../render/Shader.h"

namespace dan {
    class ImgDisp: public AbsRenderConf {
    public:
        typedef std::shared_ptr<AbsTexture> texture_t;
    private:
        texture_t texture;
        // The preferred shader, can be nullptr
        Shader *shader;
    public:
        ImgDisp(const texture_t &texture = nullptr, Shader *shader = nullptr);
        void setTexture(const texture_t &texture);
        void setShader(Shader *shader);
        texture_t &getTexture();
        Shader *getShader();

        void setup(Context &c) override;
        void render(Context &c) override;
    };
}

#endif
