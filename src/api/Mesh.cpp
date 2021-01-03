#include "Mesh.h"

#include <vector>
#include <utility>

#include "../core/util.h"

template<typename T>
std::vector<T> getTableData(sol::table data) {
    std::vector<T> result;
    result.reserve(data.size());
    for (unsigned int i = 1; i <= data.size(); i++) {
        result.push_back(data.get<T>(i));
    }
    return result;
}


dan::api::Mesh::Mesh(sol::this_state l) {
    ut::checkGLError("api::Mesh::Mesh", l);
}

dan::api::Mesh::Mesh(::dan::Mesh &&omesh): mesh(std::move(omesh)) {
}

void dan::api::Mesh::setVertices(sol::this_state l, sol::table rawData) {
    std::vector<float> data = getTableData<float>(rawData);
    mesh.setVertices(data.size(), data.data());
    ut::checkGLError("api::Mesh::setVertices", l);
}
void dan::api::Mesh::setIndices(sol::this_state l, sol::table rawData) {
    std::vector<unsigned int> data = getTableData<unsigned int>(rawData);
    mesh.setIndices(data.size(), data.data());
    ut::checkGLError("api::Mesh::setIndices", l);
}
void dan::api::Mesh::setParam(sol::this_state l, unsigned int index, int size, int stride, int offset) {
    mesh.setParam(index, size, stride, offset);
    ut::checkGLError("api::Mesh::setParam", l);
}
void dan::api::Mesh::render(sol::this_state l) {
    mesh.render();
    ut::checkGLError("api::Mesh::render", l);
}

// Static members

void dan::api::Mesh::open(sol::state_view &lua) {
    sol::usertype<Mesh> type = lua.new_usertype<Mesh>("Mesh",
        sol::constructors<Mesh(sol::this_state)>()
    );

    type["setVertices"] = &Mesh::setVertices;
    type["setIndices"] = &Mesh::setIndices;
    type["setParam"] = &Mesh::setParam;
    type["render"] = &Mesh::render;

}
