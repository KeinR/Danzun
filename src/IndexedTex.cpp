#include "IndexedTex.h"

#include <vector>

dan::IndexedTex::IndexedTex(const std::array<float, 8> &texCoords, const texture_t &texture):
    texCoords(texCoords) {

    const std::array<float, 8> coords = {
        -1, -1,
        -1, 1,
        1, 1,
        1, -1
    };

    std::vector<float> vertices;
    vertices.reserve(16);

    vertices.insert(vertices.end(), coords.cbegin(), coords.cend());
    vertices.insert(vertices.end(), texCoords.cbegin(), texCoords.cend());

    const std::array<unsigned int, 6> indices = {
        0, 1, 2,
        0, 2, 3
    };

    mesh.setIndices(indices.size(), indices.data());
    mesh.setVertices(vertices.size(), vertices.data());
}

const std::array<float, 8> &dan::IndexedTex::getTexCoords() const {
    return texCoords;
}

void dan::IndexedTex::bind() {
    texture->bind();
}

void dan::IndexedTex::render(Context &c) {
    mesh.render();
}
