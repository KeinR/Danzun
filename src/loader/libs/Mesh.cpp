#include "Mesh.h"

#include <vector>

#include "util.h"

#include "../../lib/opengl.h"
// #include "../../sprite/ManImage.h"

using namespace dan::libs::ut;

struct Mesh {
    unsigned int array;
    unsigned int vertexBuffer;
    unsigned int elementBuffer; // Is zero if we aren't using it
    unsigned int count;
};

static const char *metatable = "Mesh";

static int script_new(lua_State *L);
static int render(lua_State *L);
static int gc(lua_State *L);

static luaL_Reg funcs[] = {
    {"new", script_new},
    {"render", render},
    {"__gc", gc},
    {NULL, NULL}
};

dan::Lib dan::libs::mesh() {
    return Lib(metatable, funcs);
}

int script_new(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "new expects 1 parameter");
    }
    Mesh mesh;
    glGenVertexArrays(1, &mesh.array);
    glGenBuffers(1, &mesh.vertexBuffer);
    glBindVertexArray(mesh.array);

    std::vector<float> vertices;
    lua_getfield(L, -1, "vertices");
    luaL_getmetafield(L, -1, "__len");
    lua_pushvalue(L, -2); // self
    lua_pcall(L, 1, 1); // length // TODO: err handling
    vertices.reserve(lua_tointeger(L, -1));
    lua_pop(L, 1); // Remove return
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        vertices.push_back(lua_tointeger(L, -1));
        lua_pop(L, 1);
    }
    lua_pop(L, 1);

    glGenBuffers(1, &mesh.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    const bool drawIndices = lua_getfield(L, -1, "indices") != LUA_TNIL;
    if (drawIndices) {
        std::vector<unsigned int> indices;
        luaL_getmetafield(L, -1, "__len");
        lua_pushvalue(L, -2); // self
        lua_pcall(L, 1, 1); // length // TODO: err handling
        indices.reserve(lua_tointeger(L, -1));
        lua_pop(L, 1);
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
            indices.push_back(lua_tointeger(L, -1));
            lua_pop(L, 1);
        }
        glGenBuffers(1, &mesh.elementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.elementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        mesh.count = indices.size();
    } else {
        mesh.elementBuffer = 0;
        mesh.count = vertices.size();
    }
    lua_pop(L, 1);

    lua_getfield(L, -1, "params");
    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        int index = lua_tointeger(L, -2) - 1; // The key, -1 bc lua arrays aren't zero index'd

        int size = getIntField(L, -1, "size");
        int stride = getIntField(L, -1, "stride");
        int offset = getIntField(L, -1, "offset");

        lua_pop(L, 1);

        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(index);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    *lua_newuserdatauv(L, sizeof(Mesh), 0) = mesh;
    lua_getglobal(L, metatable);
    lua_setmetatable(L, -2);
    return 1;
}
int render(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "render expects 1 parameter");
    }
    Mesh *mesh = (Mesh *)luaL_checkudata(L, 1, metatable);
    glBindVertexArray(mesh->array);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    if (mesh->elementBuffer == 0) {
        glDrawArrays(GL_TRIANGLES, 0, mesh->count);
    } else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
        glDrawElements(GL_TRIANGLES, mesh->count, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return 0;
}
int gc(lua_State *L) {
    int top = lua_gettop(L);
    if (top != 1) {
        luaL_error(L, "__gc expects 1 parameter");
    }
    Mesh *mesh = (Mesh *)luaL_checkudata(L, 1, metatable);
    glDeleteVertexArrays(1, &mesh->array);
    glDeleteBuffers(1, &mesh->vertexBuffer);
    if (mesh->elementBuffer != 0) {
        glDeleteBuffers(1, &mesh->elementBuffer);
    }
    return 0;
}

