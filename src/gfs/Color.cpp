#include "Color.h"

#include <algorithm>
#include <cmath>

#include "../lib/opengl.h"
#include "../core/Context.h"
#include "../Shader.h"

static constexpr int LENGTH = 4;

static dan::Color::value_t valify(float p) {
    return std::round(p * 255);
}

dan::Color::Color(): Color(0.0f, 0.0f, 0.0f, 1.0f) {
}
dan::Color::Color(prop_t r, prop_t g, prop_t b, prop_t a):
    color{r, b, g, a} {
}
dan::Color::Color(hex_t hex) {
    setHex(hex);
    color[3] = 1.0f;
}

dan::Color &dan::Color::operator=(hex_t hex) {
    setHex(hex);
    return *this;
}

dan::Color::prop_t dan::Color::operator[](int index) const {
    return color[index];
}

bool dan::Color::operator==(const Color &other) const {
    constexpr float maxDev = 1.0f / 255.0f / 2.0f;
    for (int i = 0; i < LENGTH; i++) {
        // Check that the difference is greater than a deviation,
        // so as to account for floating point inaccuracies
        if (std::abs(other.color[i] - color[i]) > maxDev) {
            return false;
        }
    }
    return true;
}

bool dan::Color::operator!=(const Color &other) const {
    return !(*this == other);
}

void dan::Color::setHex(hex_t hex) {
    // We ignore the first byte
    setVal(
        (hex >> 16) & 0xFF,
        (hex >> 8) & 0xFF,
        hex & 0xFF
    );
}

void dan::Color::setVal(value_t red, value_t green, value_t blue) {
    color[0] = red / 255.0f;
    color[1] = green / 255.0f;
    color[2] = blue / 255.0f;
}

void dan::Color::setAlpha(value_t alpha) {
    color[3] = alpha / 255.0f;
}

dan::Color::hex_t dan::Color::getHex() const {
    return (valify(color[0]) << 16) | (valify(color[1]) << 8) | valify(color[2]);
}

dan::Color::prop_t *dan::Color::get() {
    // Important to be compatable with other thingies, ex OpenGL
    return color;
}

void dan::Color::load(Context &c) const {
    c.getShader().set4fv(c, "color", color);
}

dan::Color dan::Color::brighten(float percent) const {
    Color c;
    for (int i = 0; i < LENGTH; i++) {
        c.color[i] = color[i] + color[i] * percent;
        // Truncate the value if the value is too high/low
        if (c.color[i] > 1) {
            c.color[i] = 1;
        } else if (c.color[i] < 0) {
            c.color[i] = 0;
        }
    }
    return c;
}
