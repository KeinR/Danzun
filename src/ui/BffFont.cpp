#include "BffFont.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <exception>

#include "../core/error.h"
#include "../core/debug.h"
#include "../render/Mesh.h"
#include "../lib/opengl.h"

// static constexpr int VERTEX_SIZE = 8;
// Knock off colors and we get...
static constexpr int VERTEX_SIZE = 4;


static int readInt(std::ifstream &file) {
    return  (static_cast<unsigned int>(file.get()) << 0) |
            (static_cast<unsigned int>(file.get()) << 8) |
            (static_cast<unsigned int>(file.get()) << 16) |
            (static_cast<unsigned int>(file.get()) << 24);
}

dan::BffFont::BffFont(sol::state_view lua, const std::string &path): atlas({
        GL_CLAMP_TO_EDGE,
        GL_CLAMP_TO_EDGE,
        GL_NEAREST,
        GL_NEAREST
}) {

    failed = true;

    static const char *const funcSig = "BffFont::BffFont";

    std::ifstream file(path, std::ios::binary);
    if (!file.good()) {
        err(funcSig, lua) << "Failed to open \"" << path << "\"";
        return;
    }

    int imgWidth, imgHeight, channels, dataSize; 

    try {
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

        // Read header

        if (file.get() != 0xBF || file.get() != 0xF2) {
            err(funcSig, lua) << "BFF File \"" << path << "\" corrupted (header)";
            return;
        }

        imgWidth = readInt(file);
        imgHeight = readInt(file);
        cellWidth = readInt(file);
        cellHeight = readInt(file);
        channels = file.get() / 8;
        startChar = file.get();

        file.read(charWidths.data(), charWidths.size());

        constexpr int HEADER_SIZE = 276;

        file.seekg(0, file.end);
        dataSize = static_cast<int>(file.tellg()) - HEADER_SIZE;
        file.seekg(HEADER_SIZE);

        file.exceptions(std::ifstream::goodbit);

    } catch (std::exception &e) {
        err(funcSig, lua) << "Failed to read BFF file header: " << e.what();
        return;
    }

    if (dataSize == 0) {
        err(funcSig, lua) << "Cannot use empty bitmaps \"" << path << "\"";
        return;
    }

    if (dataSize != imgWidth * imgHeight * channels) {
        err(funcSig, lua) << "BFF File \"" + path + "\" corrupted (size discrepancy)";
        return;
    }

    int format = Texture::getFormat(channels);

    if (format == 0) {
        err(funcSig, lua) << "BFF File \"" + path + "\" corrupted (channels)";
    }

    char *data = new char[dataSize];
    file.read(data, dataSize);

    atlas.setData(format, imgWidth, imgHeight, reinterpret_cast<unsigned char*>(data));

    delete[] data;

    if (!file.good()) {
        err(funcSig, lua) << "Failed to read data chunk from BFF file \"" << path << "\"";
        // return // Don't return, as we can at the very least set metadata so that the font MIGHT be usable
    } else {
        failed = false;
    }

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

bool dan::BffFont::isFailed() {
    return failed;
}

int dan::BffFont::getWidth(char_t c) const {
    if (!isValidChar(c)) {
        return charWidths[0];
    }
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

bool dan::BffFont::isValidChar(unsigned char c) const {
    return c >= startChar && c <= endChar;
}

void dan::BffFont::getRenderData(std::vector<float> &vertices, std::vector<unsigned int> &indices, std::string str) const {
    DANZUN_ASSERT(str.size() > 0);

    for (char &c : str) {
        if (!isValidChar(c)) {
            c = startChar;
        }
    }

    vertices.reserve(vertices.size() + str.size() * 4 * 2 + str.size() * 4);
    indices.reserve(indices.size() + str.size() * 3 * 2);

    const int vWidth = getLinesWidth(str);
    const int vHeight = getLinesHeight(str);

    const float scaleY = static_cast<float>(getHeight()) / vHeight;

    const float nStartX = -1.0f + (0.5f) / vWidth * 2;
    const float nStartY = 1.0f - (getHeight() + 0.5f) / vHeight * 2;

    float x = nStartX + getWidth(str[0]) / vWidth * 2;
    float y = nStartY;

    const float yStep = static_cast<float>(cellHeight) / vHeight * 2 * -1;

    for (std::size_t i = 0; i < str.size(); i++) {
        unsigned char c = str[i];
        if (c == '\n') {
            if (i+1 < str.size() && isValidChar(str[i+1])) {
                x = nStartX + getWidth(str[i+1]) / vWidth * 2;
                y += yStep;
            }
        } else {
            int cw = getWidth(c);
            const float scaleX = static_cast<float>(cw) / vWidth;
            const std::array<float, 8> quad = {
                -scaleX, -scaleY,
                -scaleX, scaleY,
                scaleX, scaleY,
                scaleX, -scaleY
            };

            unsigned int vert = vertices.size() / VERTEX_SIZE;
            int index = c - startChar;
            float tx = index % rowSize * texX;
            float ty = index / rowSize * texY;
            for (int i = 0; i < 4; i++) {
                vertices.insert(vertices.end(), {
                    quad[i * 2] + x, quad[i * 2 + 1] + y,
                    texBase[i * 2] + tx, texBase[i * 2 + 1] + ty
                });
            }
            indices.insert(indices.end(), {
                vert + 0, vert + 1, vert + 2,
                vert + 0, vert + 2, vert + 3
            });

            x += static_cast<float>(cw) / vWidth * 2;
        }
    }
}

dan::Mesh dan::BffFont::genMesh(const std::string &str) const {
    Mesh mesh;

    if (str.size() == 0) {
        return mesh;
    }

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    getRenderData(vertices, indices, str);

    mesh.setVertices(vertices.size(), vertices.data());
    mesh.setIndices(indices.size(), indices.data());
    mesh.setParam(0, 2, VERTEX_SIZE, 0); // Position
    mesh.setParam(1, 2, VERTEX_SIZE, 2); // Texture coords

    return mesh;
}
