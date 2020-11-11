#include "BffFont.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>

#include "lib/opengl.h"

#include "gfs/Color.h"
#include "gfs/Mesh.h"
#include "core/error.h"
#include "core/debug.h"

static constexpr int VERTEX_SIZE = 8;


static int readInt(std::ifstream &file) {
    return  (static_cast<unsigned int>(file.get()) << 0) |
            (static_cast<unsigned int>(file.get()) << 8) |
            (static_cast<unsigned int>(file.get()) << 16) |
            (static_cast<unsigned int>(file.get()) << 24);
}

dan::BffFont::BffFont(const std::string &path) {

    std::ifstream file(path, std::ios::binary);
    if (!file.good()) {
        err("BffFont::BffFont") << "Failed to open \"" + path + "\"";
        return;
    }

    if (file.get() != 0xBF || file.get() != 0xF2) {
        err("BffFont::BffFont") << "BFF File \"" + path + "\" corrupted (header)";
        return;
    }

    int imgWidth = readInt(file);
    int imgHeight = readInt(file);
    cellWidth = readInt(file);
    cellHeight = readInt(file);
    int channels = file.get() / 8;
    startChar = file.get();

    file.read(charWidths.data(), charWidths.size());

    constexpr int HEADER_SIZE = 276;

    file.seekg(0, file.end);
    const int dataSize = static_cast<int>(file.tellg()) - HEADER_SIZE;
    file.seekg(HEADER_SIZE);

    if (dataSize != imgWidth * imgHeight * channels) {
        err("BffFont::BffFont") << "BFF File \"" + path + "\" corrupted (size)";
        return;
    }

    char *data = new char[dataSize];
    file.read(data, dataSize);

    atlas.setData(channels, imgWidth, imgHeight, reinterpret_cast<unsigned char*>(data));

    delete[] data;

    rowSize = imgWidth / cellWidth;
    int columnSize = imgHeight / cellHeight;
    endChar = std::min(startChar + rowSize * columnSize - 1, 255);
    texX = (static_cast<float>(cellWidth) * rowSize / imgWidth) / rowSize;
    texY = (static_cast<float>(cellHeight) * columnSize / imgHeight) / columnSize;
    texBase = {
        0, texY,
        0, 0,
        texX, 0,
        texX, texY
    };
}

int dan::BffFont::getWidth(char_t c) const {
    return charWidths[c];
}
int dan::BffFont::getWidth(const std::string &str) const {
    int result = 0;
    for (char c : str) {
        result += getWidth(c);
    }
    return result;
}
int dan::BffFont::getLinesWidth(const std::string &str) const {
    int most = 0;
    int current = 0;
    for (char c : str) {
        if (c == '\n') {
            if (current > most) {
                most = current;
            }
            current = 0;
        } else {
            current += getWidth(c);
        }
    }
    return most > current ? most : current;
}
int dan::BffFont::getHeight() const {
    return cellHeight;
}

int dan::BffFont::getLinesHeight(const std::string &str) const {
    int result = getHeight();
    for (char c : str) {
        if (c == '\n') {
            result += getHeight();
        }
    }
    return result;
}

void dan::BffFont::bindAtlas() {
    atlas.bind();
}

void dan::BffFont::getRenderData(std::vector<float> &vertices, std::vector<unsigned int> &indices, const std::string &str, const Color &color) const {
    DANZUN_ASSERT(str.size() > 0);

    vertices.reserve(vertices.size() + str.size() * 4 * 2 + str.size() * 4);
    indices.reserve(indices.size() + str.size() * 3 * 2);

    const int vWidth = getLinesWidth(str);
    const int vHeight = getLinesHeight(str);

    const float scaleX = static_cast<float>(cellWidth) / vWidth;
    const float scaleY = static_cast<float>(cellHeight) / vHeight;
    const std::array<float, 8> quad = {
        -scaleX, -scaleY,
        -scaleX, scaleY,
        scaleX, scaleY,
        scaleX, -scaleY
    };

    const float nStartX = -1.0f + (getWidth(str[0]) + 0.5f) / vWidth;
    const float nStartY = 1.0f - (getHeight() + 0.5f) / vHeight;

    float x = nStartX;
    float y = nStartY;

    const float yStep = static_cast<float>(cellHeight) / vHeight * 2 * -1;

    for (unsigned char c : str) {
        if (c == '\n') {
            x = nStartX;
            y += yStep;
        } else if (c < startChar || c > endChar) {
            c = startChar;
        } else {
            unsigned int vert = vertices.size() / VERTEX_SIZE;
            int index = c - startChar;
            float tx = index % rowSize * texX;
            float ty = index / rowSize * texY;
            for (int i = 0; i < 4; i++) {
                vertices.insert(vertices.end(), {
                    quad[i * 2] + x, quad[i * 2 + 1] + y,
                    texBase[i * 2] + tx, texBase[i * 2 + 1] + ty,
                    color[0], color[1], color[2], color[3]
                });
            }
            indices.insert(indices.end(), {
                vert + 0, vert + 1, vert + 2,
                vert + 0, vert + 2, vert + 3
            });

            x += static_cast<float>(getWidth(c)) / vWidth * 2;
        }
    }
}

dan::Mesh dan::BffFont::genMesh(const std::string &str, const Color &color) const {
    Mesh mesh;

    if (str.size() == 0) {
        return mesh;
    }

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    getRenderData(vertices, indices, str, color);

    mesh.setVertices(vertices.size(), vertices.data());
    mesh.setIndices(indices.size(), indices.data());
    mesh.setParam(0, 2, VERTEX_SIZE, 0); // Position
    mesh.setParam(1, 2, VERTEX_SIZE, 2); // Texture coords
    mesh.setParam(2, 4, VERTEX_SIZE, 4); // Color

    return mesh;
}