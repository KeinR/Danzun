#include "Window.h"

#include <stdexcept>
#include <string>
#include <map>

#include "WindowEvent.h"
#include "Cursor.h"
#include "Events.h"

#include "../core/debug.h"
#include "../core/error.h"
#include "../lib/glfw.h"
#include "../render/Color.h"

struct winparams {
    const char *title;
    int width;
    int height;
    int MSAASamples;
};

static void errorCallback(int error, const char* description);
static GLFWwindow *init(const winparams &p);
static void deInit();
static void initWindow(GLFWwindow *window);
static GLFWwindow *doCreateWindow(const winparams &p);
static GLFWwindow *makeWindow(const winparams &p);
static void destroyWindow(GLFWwindow *window);

static void mouseMove(GLFWwindow *window, double mouseX, double mouseY);
static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void mouseClick(GLFWwindow *window, int button, int action, int mods);
static void mouseScroll(GLFWwindow *window, double xOffset, double yOffset);
static void charCallback(GLFWwindow* window, unsigned int codepoint);

typedef std::map<GLFWwindow*, dan::WindowEvent*> eventRoots_t;
typedef eventRoots_t::iterator eventRoots_loc_t;

static int contextCount = 0;
static eventRoots_t eventRoots;

dan::Window::Window(const char *title, int width, int height, int MSAASamples):
    handle(makeWindow(winparams{title, width, height, MSAASamples}))
{
    makeCurrent();
}
dan::Window::Window(Window &&other) {
    steal(other);
}
dan::Window::~Window() {
    free();
}

dan::Window &dan::Window::operator=(Window &&other) {
    free();
    steal(other);
    return *this;
}

void dan::Window::free() {
    clearEventCallback();
    if (handle != nullptr) {
        destroyWindow(handle);
    }
}
void dan::Window::steal(Window &other) {
    handle = other.handle;
    other.handle = nullptr;
    // Event roots are tied to the handle, so there's
    // nothing else that needs to be done there.
}

void dan::Window::setCursor(const Cursor &cursor) {
    glfwSetCursor(handle, cursor.getHandle());
}
void dan::Window::setDefaultCursor() {
    glfwSetCursor(handle, NULL);
}

void dan::Window::setCursorMode(cursorMode mode) {
    int m;
    switch (mode) {
        case CURSOR_NORMAL:
            m = GLFW_CURSOR_NORMAL;
            break;
        case CURSOR_HIDDEN:
            m = GLFW_CURSOR_HIDDEN;
            break;
        case CURSOR_DISABLED:
            m = GLFW_CURSOR_DISABLED;
            break;
        default:
            return;
    }
    glfwSetInputMode(handle, GLFW_CURSOR, m);
}
void dan::Window::toggleInputMode(inputMode mode, bool toggle) {
    int m;
    switch (mode) {
        case STICKY_KEYS:
            m = GLFW_STICKY_KEYS;
            break;
        case STICKY_MOUSE_BUTTONS:
            m = GLFW_STICKY_MOUSE_BUTTONS;
            break;
        case LOCK_KEYS_MODS:
            m = GLFW_LOCK_KEY_MODS;
            break;
        case RAW_MOUSE_MOTION:
            m = GLFW_RAW_MOUSE_MOTION;
            break;
        default:
            return;
    }
    int val = toggle ? GLFW_TRUE : GLFW_FALSE;
    glfwSetInputMode(handle, m, val);
}

void dan::Window::clearColorBuffer(const Color &color) {
    glClearColor(
        color[0],
        color[1],
        color[2],
        color[3]
    );
    glClear(GL_COLOR_BUFFER_BIT);
}
void dan::Window::clearDepthBuffer() {
    glClear(GL_DEPTH_BUFFER_BIT);
}
void dan::Window::clearStencilBuffer() {
    glClear(GL_STENCIL_BUFFER_BIT);
}
void dan::Window::swapBuffers() {
    glfwSwapBuffers(handle);
}
void dan::Window::makeCurrent() {
    glfwMakeContextCurrent(handle);
}

void dan::Window::setEventCallback(WindowEvent &e) {
    eventRoots[handle] = &e;
}
void dan::Window::clearEventCallback() {
    eventRoots.erase(handle);
}

void dan::Window::setShouldClose(bool value) {
    glfwSetWindowShouldClose(handle, value);
}
bool dan::Window::shouldClose() const {
    DANZUN_ASSERT(handle != nullptr);
    return glfwWindowShouldClose(handle);
}

const char *dan::Window::getClipboardString() const {
    return glfwGetClipboardString(handle);
}
void dan::Window::setClipboardString(const char *str) {
    glfwSetClipboardString(handle, str);
}

bool dan::Window::keyPressed(keyt key) const {
    return glfwGetKey(handle, (int)key) == GLFW_PRESS;
}
dan::Window::handle_t dan::Window::getHandle() {
    return handle;
}

float dan::Window::getMouseX() const {
    double x;
    glfwGetCursorPos(handle, &x, NULL);
    return x;
}
float dan::Window::getMouseY() const {
    double y;
    glfwGetCursorPos(handle, NULL, &y);
    return y;
}
void dan::Window::getMousePos(float &x, float &y) const {
    double mx, my;
    glfwGetCursorPos(handle, &mx, &my);
    x = static_cast<float>(mx);
    y = static_cast<float>(my);
}

void dan::Window::setMousePos(float x, float y) {
    glfwSetCursorPos(handle, x, y);
}

void dan::Window::getSize(int &width, int &height) const {
    glfwGetWindowSize(handle, &width, &height);
}
int dan::Window::getWidth() const {
    int width;
    glfwGetWindowSize(handle, &width, NULL);
    return width;
}
int dan::Window::getHeight() const {
    int height;
    glfwGetWindowSize(handle, NULL, &height);
    return height;
}

int dan::Window::getFramebufferWidth() const {
    int width;
    glfwGetFramebufferSize(handle, &width, NULL);
    return width;
}
int dan::Window::getFramebufferHeight() const {
    int height;
    glfwGetFramebufferSize(handle, NULL, &height);
    return height;
}
void dan::Window::getFramebufferSize(int &width, int &height) const {
    glfwGetFramebufferSize(handle, &width, &height);
}

// Static members

void dan::Window::pollEvents() {
    glfwPollEvents();
}

void dan::Window::waitEvents() {
    glfwWaitEvents();    
}

void dan::Window::setSwapInterval(int val) {
    glfwSwapInterval(val);
}

// Internal members

void errorCallback(int error, const char* description) {
    dan::err("Window.cpp:errorCallback") << "GLFW Error [0x" << std::hex << error << std::dec << "]: " << description << '\n';
}

GLFWwindow *init(const winparams &p) {
    #define FUNC_SIG "Window.cpp:init"

    glfwSetErrorCallback(errorCallback);

    if (glfwInit() == GLFW_FALSE) {
        dan::err(FUNC_SIG, true) << "Failed to init GLFW";
        return nullptr;
    }
    // A glfw window is required to properly initialize GLAD
    GLFWwindow *window = doCreateWindow(p);
    if (window == NULL) {
        deInit();
        contextCount = 0;
        dan::err(FUNC_SIG, true) << "Failed to make GLFW window (just after init)";
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        deInit();
        contextCount = 0;
        dan::err(FUNC_SIG, true) << "Failed to initialize OpenGL loader (GLAD)";
        return nullptr;
    }
    contextCount = 1;
    return window;

    #undef FUNC_SIG
}

void deInit() {
    glfwTerminate();
}

void initWindow(GLFWwindow *window) {
    glfwSetCursorPosCallback(window, mouseMove);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseClick);
    glfwSetScrollCallback(window, mouseScroll);
    glfwSetCharCallback(window, charCallback);
}

GLFWwindow *doCreateWindow(const winparams &p) {
    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, p.MSAASamples);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // glfwWindowHint(GLFW_SCALE_TO_MONITOR, ...);

    return glfwCreateWindow(p.width, p.height, p.title, NULL, NULL);
}

GLFWwindow *makeWindow(const winparams &p) {
    GLFWwindow *window;
    if (contextCount <= 0) {
        window = init(p);
    } else {
        contextCount++;
        window = doCreateWindow(p);
        if (window == NULL) {
            dan::err("Window.cpp:makeWindow") << "Failed to make GLFW window";
            return nullptr;
        }
    }
    initWindow(window);
    return window;
}

void destroyWindow(GLFWwindow *window) {
    contextCount--;
    glfwDestroyWindow(window);
    if (contextCount <= 0) {
        deInit();
        contextCount = 0;
    }
}

void mouseMove(GLFWwindow *window, double mouseX, double mouseY) {
    eventRoots_loc_t loc = eventRoots.find(window);
    if (loc != eventRoots.end()) {
        dan::event::MouseMove e;
        e.x = mouseX;
        e.y = mouseY;
        loc->second->mouseMoved(e);
    }
}
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    eventRoots_loc_t loc = eventRoots.find(window);
    if (loc != eventRoots.end()) {
        dan::event::KeyPress e;
        e.key = (dan::keyt)key;
        e.action = (dan::keyAction)action;
        e.mods = dan::KeyMods(mods);
        loc->second->keyPressed(e);
    }
}


void mouseClick(GLFWwindow *window, int button, int action, int mods) {
    eventRoots_loc_t loc = eventRoots.find(window);
    if (loc != eventRoots.end()) {
        dan::event::MouseClick e;
        e.button = (dan::mouseButton)button;
        e.pressed = action == GLFW_PRESS;
        e.mods = dan::KeyMods(mods);
        loc->second->mouseClicked(e);
    }
}
void mouseScroll(GLFWwindow *window, double xOffset, double yOffset) {
    eventRoots_loc_t loc = eventRoots.find(window);
    if (loc != eventRoots.end()) {
        dan::event::MouseScroll e;
        e.xOffset = xOffset;
        e.yOffset = yOffset;
        loc->second->mouseScrolled(e);
    }
}
void charCallback(GLFWwindow* window, unsigned int codepoint) {
    eventRoots_loc_t loc = eventRoots.find(window);
    if (loc != eventRoots.end()) {
        dan::event::CharInput e;
        e.codepoint = codepoint;
        loc->second->charInput(e);
    }
}
