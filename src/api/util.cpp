#include "util.h"

#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "../core/error.h"

static std::string stripAseExt(const std::string &in);

sol::table dan::api::util::loadAsepriteJSONArray(sol::this_state l, const std::string &path) {
#define FUNC_SIG "api::Image::getFramesAseprite"

    sol::state_view lua = l;
    sol::table results = lua.create_table();

    // Number-{width,height,duration,coords{...}} pairs
    sol::table array = lua.create_table();
    // String-number pairs
    sol::table hash = lua.create_table();

    results["array"] = array;
    results["hash"] = hash;

    try {
        std::ifstream file(path);
        if (!file.good()) {
            err(FUNC_SIG) << "\"" << path << "\" does not exist or cannot be opened";
            return results;
        }

        using json = nlohmann::json;
        json root = json::parse(file);

        file.close();

        // Const Json rEFrence
        typedef const json& cjef;

        cjef metadata = root.at("meta");

        cjef size = metadata.at("size");
        float imgWidth = size.at("w").get<int>();
        float imgHeight = size.at("h").get<int>();

        cjef dataFrames = root.at("frames");
        for (json::size_type i = 0; i < dataFrames.size(); i++) {
            cjef frm = dataFrames[i];
            cjef info = frm.at("frame");

            float x = info.at("x").get<int>();
            float y = info.at("y").get<int>();
            float width = info.at("w").get<int>();
            float height = info.at("h").get<int>();

            sol::table data = lua.create_table();
            data["width"] = width;
            data["height"] = height;
            data["duration"] = frm.at("duration").get<int>() / 1000.0f; // Convert to seconds
            data["coords"] = {
                x / imgWidth, (y + height) / imgHeight,
                x / imgWidth, y / imgHeight,
                (x + width) / imgWidth, y / imgHeight,
                (x + width) / imgWidth, (y + height) / imgHeight
            };

            array.add(data);
            hash[stripAseExt(frm.at("filename").get<std::string>())] = array.size(); // This is OK, since Lua arrays aren't zero-index'd
        }
    } catch (std::exception &e) {
        err(FUNC_SIG) << "Failed to parse JSON \"" << path << "\": " << e.what();
    }

    return results;

#undef FUNC_SIG
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

void dan::api::util::open(sol::state_view lua) {
    sol::table t = lua.create_table();
    lua["util"] = t;

    t["loadAsepriteFrames"] = &loadAsepriteJSONArray;
}
