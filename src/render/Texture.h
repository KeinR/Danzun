#ifndef DANZUN_TEXTURE_H_INCLUDED
#define DANZUN_TEXTURE_H_INCLUDED

#include <string>

#include "../sprite/AbsTexture.h"

namespace dan {
    class Image;
    class Context;
}

namespace dan {
    class Texture: public AbsTexture {
    public:
        /// Type of data accepted by the Texture
        /// @see setData(int format, unsigned int width, unsigned int height, const data_t *data)
        typedef unsigned char data_t;

        /**
        * tparam's parameters are used to give
        * OpenGL filtering configurations to
        * the texture.
        * x/yWrap specify how to wrap the texture.
        * Possible values are GL_CLAMP_TO_EDGE, GL_MIRRORED_REPEAT, or GL_REPEAT
        * min/max filter specifies how to filter the texture when it's being
        * scaled down or up respectively.
        * Possible values are GL_NEAREST and GL_LINEAR
        * @see setDefaultParams()
        * @see setParams(const tparam &params)
        */
        struct tparam {
            /// OpenGL enum for GL_TEXTURE_WRAP_S
            int xWrap;
            /// OpenGL enum for GL_TEXTURE_WRAP_T
            int yWrap;

            /// OpenGL enum for GL_TEXTURE_MIN_FILTER
            int minFilter;
            /// OpenGL enum for GL_TEXTURE_MAG_FILTER
            int maxFilter;
        };

        /// The default parameters.
        /// @see setDefaultParams()
        static const tparam defaultParams;

    private:
        /// Handle to the managed OpenGL buffer
        unsigned int buffer;

        int iWidth;
        int iHeight;

        /**
        * Initializes the Texture.
        * Creates the actual @ref buffer
        * @param [in] params Parameters to be set
        */
        void init(const tparam &param);

        /**
        * Frees managed resources.
        * @see buffer
        */
        void deInit();

        /**
        * Takes ownership of `other`'s @ref buffer
        * @param [in,out] other Target
        */
        void steal(Texture &other);
    public:
        enum format {
            RGBA,
            RGB,
            RG,
            RED,
            INVALID_FORMAT
        };

        /**
        * Creates a texture object and applies the default parameters.
        * @see setDefaultParams()
        */
        Texture();
        /**
        * Creates a texture object and applies given parameters.
        * @param [in] params Texture parameters
        * @see setParams(const tparam &params)
        */
        Texture(const tparam &params);
        /**
        * Destuct the texture object, destroying the managed
        * texture object - if it hasn't been moved.
        */
        ~Texture();
        /**
        * Initialize by taking ownership of `other`'s buffer
        * @param [in,out] other Target
        */
        Texture(Texture &&other);
        /**
        * Take ownership of `other`'s buffer,
        * and destroy `*this`'s
        * @param [in,out] other Target
        */
        Texture &operator=(Texture &&other);

        /**
        * Gets the wrapped OpenGL buffer, @ref buffer.
        * @return @ref buffer
        */
        unsigned int getHandle();

        void loadImage(const std::string &imgPath, bool flipOnLoad = true);
        void setImage(const Image &image);

        /**
        * Sets this texture as current, so that it'll be used in
        * whatever texture slot is active (via glActiveTexture(...))
        */
        void bind() override;
        static void unbind();

        /**
        * Set the content of the texture.
        * @param [in] format OpenGL enum value describing the data format [<a href="https://www.khronos.org/opengl/wiki/Image_Format">wiki</a>]
        * @param [in] width The @e pixel width of the texture
        * @param [in] height The @e pixel height of the texture
        * @param [in] data Pointer to the raw pixel data.
        */
        void setData(format fmt, unsigned int width, unsigned int height, const data_t *data);
        void setData(int channels, unsigned int width, unsigned int height, const data_t *data);
        // Reduces data to zero.
        // Equivilent to setData(Texture::[RGBA], 0, 0, NULL)
        void clear();

        /**
        * Generates a mipmap for the texture.
        */
        void genMipmap();

        /**
        * Resets the filtering and wrapping parameters to their defaults
        * @see defaultParams
        */
        void setDefaultParams();
        /**
        * Changes the filtering and wrapping parameters
        * @param [in] params The desiried parameters
        * @see tparam
        */
        void setParams(const tparam &params);

        int getWidth();
        int getHeight();

        void render(Context &c) override;

        // Returns INVALID_FORMAT if `channels` < 1 or > 4
        static format getFormat(int channels);
    };
}

#endif