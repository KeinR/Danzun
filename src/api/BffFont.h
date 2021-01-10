#ifndef DANZUN_API_BFFFONT_H_INCLUDED
#define DANZUN_API_BFFFONT_H_INCLUDED

#include <memory>

#include <sol/sol.hpp>

#include "../ui/BffFont.h"
#include "Mesh.h"

namespace dan::api {
    class BffFont {
        std::shared_ptr<::dan::BffFont> font;
    public:
        /**
         * Constructs a BffFont
         * \param l The current state
         * \param path The path to the BFF file
         * */
        BffFont(sol::this_state l, const std::string &path);

        /**
         * Check if the font is invalid (ie, failed to load )
         * \return true if invalid
         * */
        bool isFailed();

        /**
         * Get the pixel width of one char
         * \param c The char
         * \return The width
         * */
        int getCharWidth(char c) const;
        /**
         * Gets the width of a sequence of characters,
         * ignoring newlines.
         * \param str The string
         * \return The pixel width
         * \see getCharWidth
         * */
        int getStrWidth(const std::string &str) const;
        /**
         * Gets the length of the longest contiguous line segment, deliminated by newline characters (LF)
         * \param str The string
         * \return The width, in pixels
         * */
        int getLinesWidth(const std::string &str) const;
        /**
         * Gets the height of any one line in pixels
         * \return The height in pixels
         * */
        int getHeight() const;
 
        /**
         * Gets the likely height of the string if newlines are considered.
         * Effectively counts the number of newlines, adds 1, then multiplies by
         * \ref getHeight
         * \param str The string
         * \return The height, in pixels
         * */
        int getLinesHeight(const std::string &str) const;
        /**
         * Binds the texture atlas used by this font
         * \oaram l The current state
         * */
        void bind(sol::this_state l);

        /**
         * Generates vertex data from a string that can be used to render text from the texture atlas
         * The vertices come in sets of 16 for each character, with 4 values for each vertex.
         * The first two are the x/y positions, the second two are the texture coordinates.
         * The indices point to the indices as they are ordered, with 6 per character.
         * \oaram str The string to reference from 
         * \param vertices Table to store the vertices
         * \param indices Table to store the indices
         * */
        void getVertexData(const std::string &str, sol::table vertices, sol::table indices);

        /**
         * Creates a mush from the result of \ref getVertexData
         * \param l The current state
         * \param str The string
         * \return The mesh
         * */
        Mesh makeMesh(sol::this_state l, const std::string &str);

        /**
         * Registers this class with the given Lua state
         * \param lua The lua state
         * */
        static void open(sol::state_view lua);
    };
}

#endif

