#ifndef DANZUN_INDEXEDTEX_H_INCLUDED
#define DANZUN_INDEXEDTEX_H_INCLUDED

#include <array>
#include <memory>

#include "AbsTexture.h"

#include "../render/Texture.h"
#include "../render/Mesh.h"

namespace dan {
    class IndexedTex: public AbsTexture {
    public:
        typedef std::shared_ptr<Texture> texture_t;
    private:
        Mesh mesh;
        texture_t texture;
        std::array<float, 8> texCoords;
    public:
        IndexedTex(const std::array<float, 8> &texCoords, const texture_t &texture);
        const std::array<float, 8> &getTexCoords() const;
        void bind() override;
        void render(Context &c) override;
    };
}

#endif
