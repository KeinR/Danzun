#include "Mesh.h"

#include <vector>

template<typename T>
std::vector<T> getTableData(sol::table data) {
    std::vector<T> result;
    result.reserve(data.size());
    for (unsigned int i = 1; i <= data.size(); i++) {
        result.push_back(data.get<T>(i));
    }
    return result;
}


dan::api::Mesh::Mesh() {
}
void dan::api::Mesh::setVertices(sol::table rawData) {
    std::vector<float> data = getTableData<float>(rawData);
    mesh.setVertices(data.size(), data.data());
}
void dan::api::Mesh::setIndices(sol::table rawData) {
    std::vector<unsigned int> data = getTableData<unsigned int>(rawData);
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
    sol::usertype<Mesh> type = lua.new_usertype<Mesh>("Mesh",
        sol::constructors<Mesh()>()
    );

    type["setVertices"] = &Mesh::setVertices;
    type["setIndices"] = &Mesh::setIndices;
    type["setParam"] = &Mesh::setParam;
    type["render"] = &Mesh::render;

}
