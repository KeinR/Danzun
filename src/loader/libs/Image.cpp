#include "Image.h"

#include "util.h"

#include "../../lib/opengl.h"
#include "../../sprite/ManImage.h"

using namespace dan::libs::ut;

struct Image {
    int handle;
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
    return Lib("Image", funcs);
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
            luaL_error(L, "Invalid # of channels in image");
            return;
    }
    int handle;
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

    Image *img = (Image *)lua_touserdata(L, 1);
    lua_getfield(L, 2, "x");
    int x = lua_tonumber(L, -1);
    lua_getfield(L, 2, "y");
    int y = lua_tonumber(L, -1);
    lua_getfield(L, 2, "width");
    int width = lua_tonumber(L, -1);
    lua_getfield(L, 2, "height");
    int height = lua_tonumber(L, -1);
    lua_getfield(L, 2, "rotation");
    int height = lua_tonumber(L, -1);
    lua_pop(L, 5);

    glBindTexture(GL_TEXTURE_2D, img->handle);

    getProgram(L).getEngine().getContext().renderQuad();

    return 0;
}
int gc(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 2) {
        luaL_error(L, "__gc expects 1 parameter");
    }
    Image *img = (Image *)lua_touserdata(L, 1);
    glDeleteTextures(1, &img->buffer);
    return 0;
}
