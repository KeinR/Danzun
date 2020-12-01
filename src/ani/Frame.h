#ifndef DANZUN_FRAME_H_INLCUDED
#define DANZUN_FRAME_H_INLCUDED

#include <memory>

#include "../sprite/AbsTexture.h"
#include "../render/Shader.h"

namespace dan {
    class Context;
}

namespace dan {
    class Frame {
    public:
        // Should prob be ImgDisp but not important
        typedef std::shared_ptr<AbsTexture> texture_t;
    private:
        texture_t texture;
        // In seconds
        float length;
        // The preferred shader, can be nullptr (will not be set)
        Shader *shader;
    public:
        Frame(const texture_t &texture, float length, Shader *shader = nullptr);
        float getLength() const;

        void setup(Context &c);
        void render(Context &c);
    };
}

#endif
