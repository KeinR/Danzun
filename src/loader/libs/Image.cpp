#include "Image.h"

#include <lua/lua.hpp>

#include "util.h"

#include "../../lib/opengl.h"
#include "../../sprite/ManImage.h"
#include "../../render/Matrix.h"
#include "../Program.h"

using namespace dan::libs::ut;

const char *metatable = "Image";

struct Image {
    unsigned int handle;
};

static int script_new(lua_State *L);
static int render(lua_State *L);
static int gc(lua_State *L);

static luaL_Reg funcs[] = {
    {"new", script_new},
    {"render", render},
    {"__gc", gc},
    {NULL, NULL}
};

dan::Lib dan::libs::image() {
    return Lib(metatable, funcs);
}

int script_new(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "render expects 1 parameter");
    }
    
    std::string path = getString(L, 1);

    dan::ManImage image(path);
    int format;
    switch (image.getChannels()) {
        case 4: format = GL_RGBA; break;
        case 3: format = GL_RGB; break;
        case 2: format = GL_RG; break;
        case 1: format = GL_RED; break;
        default:
            // Do long jumps result in C++ destructors being called?
            // I mean, I don't see why not, but still...
            luaL_error(L, "Invalid # of channels in image");
    }
    unsigned int handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexImage2D(GL_TEXTURE_2D, 0, format, image.getWidth(), image.getHeight(), 0, format, GL_UNSIGNED_BYTE, image.getData());
    glBindTexture(GL_TEXTURE_2D, 0);

    Image *img = (Image *)lua_newuserdatauv(L, sizeof(Image), 0);
    img->handle = handle;
    lua_getglobal(L, "Image");
    lua_setmetatable(L, -2);

    return 1;
}
int render(lua_State *L) {
    int top = lua_gettop(L);
    if (top < 2) {
        luaL_error(L, "render expects at least 2 parameters");
    }
    // self, object{x,y,w,h}, [mesh]

    Image *img = (Image *)luaL_checkudata(L, 1, metatable);
    int x = getIntField(L, 2, "x");
    int y = getIntField(L, 2, "y");
    int width = getIntField(L, 2, "width");
    int height = getIntField(L, 2, "height");

    dan::Matrix(x, y, width, height).load(getProgram(L).getEngine().getContext());

    glBindTexture(GL_TEXTURE_2D, img->handle);

    // Mesh object is not provided
    if (top < 3) {
        lua_getglobal(L, "_dan");
        lua_getfield(L, -1, "defaults");
    }
    lua_getfield(L, -1, "mesh");
    lua_getfield(L, -1, "render");
    lua_pushvalue(L, -2);
    lua_call(L, 1, 0);

    return 0;
}
int gc(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 2) {
        luaL_error(L, "__gc expects 1 parameter");
    }
    Image *img = (Image *)luaL_checkudata(L, 1, metatable);
    glDeleteTextures(1, &img->handle);
    return 0;
}
