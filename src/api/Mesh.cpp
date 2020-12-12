#include "Mesh.h"

#include <vector>

template<typename T>
std::vector<T> getTableData(sol::table data) {
    std::vector<T> result;
    result.reserve(data.size());
    for (int i = 1; i <= data.size(); i++) {
        result.push_back(data.get<T>(i));
    }
    return result;
}


dan::api::Mesh() {
}
void dan::api::Mesh::setVertices(sol::table data) {
    std::vector<float> data = getTableData<float>(data);
    mesh.setVertices(data.size(), data.data());
}
void dan::api::Mesh::setIndices(sol::table data) {
    std::vector<unsigned int> data = getTableData<unsigned int>(data);
    mesh.setIndices(data.size(), data.data());
}
void dan::api::Mesh::setParam(unsigned int index, int size, int stride, int offset) {
    mesh.setParam(index, size, stride, offset);
}
void dan::api::Mesh::render() {
    mesh.render();
}

// Static members

void dan::api::Mesh::open(sol::state_view &lua) {
    sol::usertype<Mesh> type = lua.new_usertype<Mesh>("Mesh", sol::constructors<Mesh()>());

    type["setVertices"] = &setVertices;
    type["setIndices"] = &setIndices;
    type["setParam"] = &setParam;
    type["render"] = &render;

}
