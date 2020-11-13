#include "Atlas.h"

#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "core/debug.h"
#include "core/error.h"
#include "ManImage.h"
#include "util.h"
#include "Frame.h"
#include "IndexedTex.h"

static constexpr int CHANNELS = 4;

static std::string stripAseExt(const std::string &in);

dan::Atlas::Atlas(): texture(std::make_shared<Texture>()) {
}

dan::Atlas &dan::Atlas::loadAse(const std::string &path) {
    try {
        namespace fs = std::filesystem;

        fs::path realPath = fs::canonical(path);

        std::string strPath = realPath.string();

        std::ifstream file(realPath);
        if (!file.good()) {
            err("Atlas::loadAse") << "\"" << path << "\" does not exist or cannot be opened";
            return *this;
        }

        using json = nlohmann::json;
        json root = json::parse(file);

        file.close();

        // Const Json rEFrence
        typedef const json& cjef;

        cjef metadata = root.at("meta");

        std::string imagePath = metadata.at("image").get<std::string>();
        texture->setImage(ManImage(ut::dirname(path) + imagePath, false, CHANNELS));

        cjef size = metadata.at("size");
        float imgWidth = size.at("w").get<int>();
        float imgHeight = size.at("h").get<int>();

        frames.clear();
        frameMap.clear();

        cjef dataFrames = root.at("frames");
        for (json::size_type i = 0; i < dataFrames.size(); i++) {
            cjef frm = dataFrames[i];
            cjef info = frm.at("frame");
            float x = info.at("x").get<int>();
            float y = info.at("y").get<int>();
            float width = info.at("w").get<int>();
            float height = info.at("h").get<int>();
            frame data;
            data.width = width;
            data.height = height;
            data.duration = frm.at("duration").get<int>() / 1000.0f;
            data.coords = {
                x / imgWidth, (y + height) / imgHeight,
                x / imgWidth, y / imgHeight,
                (x + width) / imgWidth, y / imgHeight,
                (x + width) / imgWidth, (y + height) / imgHeight
            };
            frames.push_back(data);
            frameMap[stripAseExt(frm.at("filename").get<std::string>())] = frames.size() - 1;
        }
    } catch (std::exception &e) {
        err("Atlas::loadAse") << "Failed to load atlas as specified in \"" << path << "\": " << e.what();
    }

    return *this;
}

std::shared_ptr<dan::Texture> &dan::Atlas::getTexture() {
    return texture;
}
dan::Atlas::frame &dan::Atlas::getFrame(unsigned int index) {
    DANZUN_ASSERT(index < frames.size());
    return frames[index];
}
dan::Atlas::frame &dan::Atlas::getFrame(const std::string &name) {
    frameMap_t::iterator it = frameMap.find(name);
    DANZUN_ASSERT(it != frameMap.end());
    return frames[it->second];
}

std::string stripAseExt(const std::string &in) {
    if (in.size() > 4) {
        std::string ext = in.substr(in.size() - 4);
        if (ext == ".ase") {
            return in.substr(0, in.size() - 4);
        }
    }
    return in;
}

dan::Animation dan::Atlas::asAnimation(AniControl *c) const {
    Animation ani(c);
    for (frame f : frames) {
        ani.pushFrame(dan::Frame(
            std::make_shared<dan::IndexedTex>(
                f.coords,
                texture
            ),
            f.duration
        ));
    }
    return ani;
}
