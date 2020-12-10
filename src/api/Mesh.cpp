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
void dan::api::setVertices(sol::table data) {
    std::vector<float> data = getTableData<float>(data);
    mesh.setVertices(data.size(), data.data());
}
void dan::api::setIndices(sol::table data) {
    std::vector<unsigned int> data = getTableData<unsigned int>(data);
    mesh.setIndices(data.size(), data.data());
}
void dan::api::setParam(unsigned int index, int size, int stride, int offset) {
    mesh.setParam(index, size, stride, offset);
}
void dan::api::render() {
    mesh.render();
}

// Static members

void open(sol::state_view &lua) {

}
