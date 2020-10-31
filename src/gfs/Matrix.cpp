#include "Matrix.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "../lib/opengl.h"
#include "../core/Context.h"
#include "../Shader.h"

inline static float ndcX(float x, int winWidth);
inline static float ndcY(float y, int winHeight);
inline static glm::mat4 reflectYAxis(const glm::mat4 &m);

dan::Matrix::Matrix(float x, float y, float width, float height, float rotation, bool reflectAcrossYAxis):
    x(x), y(y), width(width), height(height), rotation(rotation), reflectAcrossYAxis(reflectAcrossYAxis) {
}

void dan::Matrix::load(Context &c) {
    glm::mat4 model(1.0f);

    const float s = ndcX(x + width / 2, c.getVPWidth());
    const float t = ndcY(y + height / 2, c.getVPHeight());

    model = glm::translate(model, glm::vec3(s, t, 0));

    const float xScale = width / c.getVPWidth();
    const float yScale = height / c.getVPHeight();

    model = glm::scale(model, glm::vec3(xScale, yScale, 0));

    const float radians = glm::radians(rotation);

    model = glm::rotate(model, radians, glm::vec3(0, 0, 1));

    if (reflectAcrossYAxis) {
        model = reflectYAxis(model);
    }

    c.getShader()->setMatrix4fv("model", glm::value_ptr(model));
}

float ndcX(float x, int winWidth) {
    return x / winWidth * 2 - 1;
}

float ndcY(float y, int winHeight) {
    return (y / winHeight * 2 - 1) * -1;
}

glm::mat4 reflectYAxis(const glm::mat4 &m) {
    glm::mat4 r(1.0f);
    r[0][0] = -1.0f;

    return m * r;
}
