#ifndef DANZUN_API_IMAGE_H_INCLUDED
#define DANZUN_API_IMAGE_H_INCLUDED

#include <string>

#include <sol/sol.hpp>

#include "../render/Texture.h"

namespace dan::api {
    /**
     * A simple image loaded as an OpenGL texture.
     * Still preserves some useful metadata.
     * */
    class Image {
        /// The native OpenGL texture
        ::dan::Texture tex;
        /// The original image width (pixels)
        int width;
        /// The original image height (pixels)
        int height;
        /// If the image failed to load or is otherwise in an invalid state
        bool failed;
    public:
        /**
         * Overload that calls the other ctor with flipped as false
         * */
        Image(sol::this_state l, const std::string &path);
        /**
         * Construct an image, loading one from the given path.
         * \param l The current state
         * \param path The path to the image file
         * \param loadFlipped Set to true for the image to be flipped vertically on load
         * */
        Image(sol::this_state l, const std::string &path, bool loadFlipped);

        /**
         * Binds this image
         * \param l The current state
         * */
        void bind(sol::this_state l);

        /**
         * Get the original width of the image
         * \return The width in pixels
         * */
        int getWidth();
        /**
         * Get the original height of the image
         * \return The height in pixels
         * */
        int getHeight();
        /**
         * Check if the image failed ot load or is otherwise in
         * an invalid state.
         * If this returns true, do not use!
         * \return true if invalid
         * */
        bool isFailed();

        /**
         * Registers this class with the given state
         * \param lua The state
         * */
        static void open(sol::state_view lua);
    };
}

#endif
