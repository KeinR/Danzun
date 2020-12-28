

#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat4 model;

out vec2 pos;

void main() {
    gl_Position = model * vec4(aPos, 0, 1);
    pos = aPos;
}
