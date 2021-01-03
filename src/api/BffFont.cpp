#include "BffFont.h"

#include <vector>

#include "../core/error.h"

dan::api::BffFont::BffFont(sol::this_state l, const std::string &path) {
    font = std::make_shared<::dan::BffFont>(l, path);
}

bool dan::api::BffFont::isFailed() {
    return font->isFailed();
}

int dan::api::BffFont::getCharWidth(char c) const {
    return font->getWidth(c);
}
int dan::api::BffFont::getStrWidth(const std::string &str) const {
    return font->getWidth(str);
}

int dan::api::BffFont::getLinesWidth(const std::string &str) const {
    return font->getLinesWidth(str);
}
int dan::api::BffFont::getHeight() const {
    return font->getHeight();
}
int dan::api::BffFont::getLinesHeight(const std::string &str) const {
    return font->getLinesHeight(str);
}

void dan::api::BffFont::bind() {
    font->bindAtlas();
}

void dan::api::BffFont::getVertexData(const std::string &str, sol::table vertices, sol::table indices) {
    std::vector<float> vert;
    std::vector<unsigned int> ind;
    font->getRenderData(vert, ind, str);
    for (float v : vert) {
        vertices.add(v);
    }
    for (unsigned int v : ind) {
        indices.add(v);
    }
}

dan::api::Mesh dan::api::BffFont::makeMesh(const std::string &str) {
    return Mesh(font->genMesh(str));
}

// Static members

void dan::api::BffFont::open(sol::state_view lua) {
    sol::usertype<BffFont> type = lua.new_usertype<BffFont>("BffFont",
        sol::constructors<BffFont(sol::this_state,const std::string&)>()
    );

    type["getCharWidth"] = &BffFont::getCharWidth;
    type["getStrWidth"] = &BffFont::getStrWidth;
    type["getLinesWidth"] = &BffFont::getLinesWidth;
    type["getHeight"] = &BffFont::getHeight;
    type["getLinesHeight"] = &BffFont::getLinesHeight;
    type["bind"] = &BffFont::bind;
    type["getVertexData"] = &BffFont::getVertexData;
    type["makeMesh"] = &BffFont::makeMesh;
    type["failed"] = sol::property(&BffFont::isFailed);

}
