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
        BffFont(sol::this_state l, const std::string &path);

        bool isFailed();

        int getCharWidth(char c) const;
        int getStrWidth(const std::string &str) const;

        int getLinesWidth(const std::string &str) const;
        int getHeight() const;
        int getLinesHeight(const std::string &str) const;

        void bind();

        void getVertexData(const std::string &str, sol::table vertices, sol::table indices);

        Mesh makeMesh(const std::string &str);

        static void open(sol::state_view lua);
    };
}

#endif
