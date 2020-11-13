#include "ManImage.h"

#include <stb/stb_image.h>

#include "../core/error.h"

dan::ManImage::ManImage(): data(nullptr), width(0), height(0), channels(0) {
}
dan::ManImage::ManImage(const std::string &path, bool flipOnLoad, int desiredChannels) {
    stbi_set_flip_vertically_on_load(flipOnLoad);
    data = stbi_load(path.c_str(), &width, &height, &channels, desiredChannels);
    if (data == NULL) {
        err("ManImage::ManImage(...)") << "Failed to load image \"" << path << "\"";
    }
}
dan::ManImage::ManImage(ManImage &&other) {
    steal(other);
}
dan::ManImage::~ManImage() {
    free();
}

void dan::ManImage::free() {
    if (data != nullptr) {
        stbi_image_free(data);
    }
}

void dan::ManImage::steal(ManImage &other) {
    data = other.data;
    width = other.width;
    height = other.height;
    channels = other.channels;
    other.data = nullptr;
}

dan::ManImage &dan::ManImage::operator=(ManImage &&other) {
    free();
    steal(other);
    return *this;
}

int dan::ManImage::getWidth() const {
    return width;
}
int dan::ManImage::getHeight() const {
    return height;
}
int dan::ManImage::getChannels() const {
    return channels;
}
int dan::ManImage::getSize() const {
    return width * height * channels;
}
unsigned char *dan::ManImage::getData() const {
    return data;
}
