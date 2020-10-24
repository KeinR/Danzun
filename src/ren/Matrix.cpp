#include "Matrix.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "opengl.h"
#include "util.h"
#include "RenderContext.h"

static inline glm::mat4 reflectYAxis(const glm::mat4 &m);

dan::Matrix::Matrix(float x, float y, float z, float width, float height, float rotation, bool reflectAcrossYAxis):
    x(x), y(y), z(z), width(width), height(height), rotation(rotation), reflectAcrossYAxis(reflectAcrossYAxis) {
}

void dan::Matrix::load(const RenderContext &info) {
    glm::mat4 model(1.0f);

    const float s = ut::ndcX(x + width / 2 + info.getPanX(), info.getFrameWidth());
    const float t = ut::ndcY(y + height / 2 + info.getPanY(), info.getFrameHeight());

    model = glm::translate(model, glm::vec3(s, t, z));

    const float xScale = width / info.getFrameWidth() * info.getZoom();
    const float yScale = height / info.getFrameHeight() * info.getZoom();

    model = glm::scale(model, glm::vec3(xScale, yScale, 0));

    const float radians = glm::radians(rotation);

    model = glm::rotate(model, radians, glm::vec3(0, 0, 1));

    if (reflectAcrossYAxis) {
        model = reflectYAxis(model);
    }

    glUniformMatrix4fv(info.getMatrixLocation(), 1, GL_FALSE, glm::value_ptr(model));
}

glm::mat4 reflectYAxis(const glm::mat4 &m) {
    glm::mat4 r(1.0f);
    r[0][0] = -1.0f;

    return m * r;
}
