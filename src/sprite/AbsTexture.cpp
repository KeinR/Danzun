#include "AbsTexture.h"

dan::AbsTexture::~AbsTexture() {
}

void dan::AbsTexture::setup(Context &c) {
    bind();
}
