#include "Image.h"

#include <stb/stb_image.h>

#include <stdexcept>

dan::api::Image::Image(const std::string &path) {

    stbi_set_flip_vertically_on_load(true);
    int channels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (data == NULL) {
        throw std::invalid_argument("Failed to open image file");
    }

    int format = Texture::getFormat(channels);

    if (format != 0) {
        tex.setData(format, width, height, data);
        stbi_image_free(data);
    } else {
        stbi_image_free(data);
        throw std::invalid_argument("Failed to parse image");
    }
}

void dan::api::Image::bind() {
    tex.bind();
}

void dan::api::Image::open(sol::state_view lua) {
    sol::usertype<Image> type = lua.new_usertype<Image>("Image",
        sol::constructors<Image(const std::string&)>()
    );

    type["bind"] = &Image::bind;
    // NB: Performance degredation when mixing variables and functions in userdata
    type["width"] = sol::readonly(&Image::width);
    type["height"] = sol::readonly(&Image::height);

}
