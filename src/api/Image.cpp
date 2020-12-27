#include "Image.h"

#include <stb/stb_image.h>

#include "../core/error.h"

dan::api::Image::Image(sol::this_state l, const std::string &path) {

    failed = true;

    stbi_set_flip_vertically_on_load(true);
    int channels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (data == NULL) {
        err("api::Image::Image", l) << "Failed to load image from \"" << path << "\"";
        return;
    }

    int format = Texture::getFormat(channels);

    if (format != 0) {
        tex.setData(format, width, height, data);
        stbi_image_free(data);
        failed = false;
    } else {
        stbi_image_free(data);
        err("api::Image::Image", l) << "Invalid image format for \"" << path << "\" (channels=" << channels << ")";
    }
}

void dan::api::Image::bind() {
    tex.bind();
}

int dan::api::Image::getWidth() {
    return width;
}
int dan::api::Image::getHeight() {
    return height;
}

bool dan::api::Image::isFailed() {
    return failed;
}

void dan::api::Image::open(sol::state_view lua) {
    sol::usertype<Image> type = lua.new_usertype<Image>("Image",
        sol::constructors<Image(sol::this_state,const std::string&)>()
    );

    type["bind"] = &Image::bind;
    // NB: Performance degredation when mixing variables and functions in userdata
    type["width"] = sol::property(&Image::getWidth);
    type["height"] = sol::property(&Image::getHeight);
    type["failed"] = sol::property(&Image::isFailed);

}
