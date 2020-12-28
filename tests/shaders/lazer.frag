#version 330 core
out vec4 FragColor;

uniform vec4 color;

in vec2 pos;

void main() {
    float m = length(pos);
    if (pos.y < 0 && m > 1) {
        discard;
    }
    FragColor = color * m;
}
