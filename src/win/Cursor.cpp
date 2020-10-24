#include "Cursor.h"

#include "../lib/glfw.h"
#include "../core/error.h"

dan::Cursor::Cursor(): Cursor(nullptr) {
}
dan::Cursor::Cursor(cursorType type) {
    int t;
    switch (type) {
        case ARROW:
            t = GLFW_ARROW_CURSOR;
            break;
        case IBEAM:
            t = GLFW_IBEAM_CURSOR;
            break;
        case CROSSHAIR:
            t = GLFW_CROSSHAIR_CURSOR;
            break;
        case HAND:
            t = GLFW_HAND_CURSOR;
            break;
        case HRESIZE:
            t = GLFW_HRESIZE_CURSOR;
            break;
        case VRESIZE:
            t = GLFW_VRESIZE_CURSOR;
            break;
        default:
            err("Cursor::Cursor") << "Invalid enum";
            return;
    }
    handle = glfwCreateStandardCursor(t);
    if (handle == NULL) {
        err("Cursor::Cursor") << "Failed to create standard cursor";
    }
}
dan::Cursor::Cursor(GLFWcursor *handle): handle(handle) {
}
dan::Cursor::Cursor(Cursor &&other) {
    steal(other);
}
dan::Cursor::~Cursor() {
    free();
}

dan::Cursor &dan::Cursor::operator=(Cursor &&other) {
    free();
    steal(other);
    return *this;
}

void dan::Cursor::steal(Cursor &other) {
    handle = other.handle;
    other.handle = nullptr;
}
void dan::Cursor::free() {
    if (handle != nullptr) {
        glfwDestroyCursor(handle);
    }
}

GLFWcursor *dan::Cursor::getHandle() const {
    return handle;
}
