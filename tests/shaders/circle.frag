#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D tex;
uniform vec4 color;

void main() {
    FragColor = texture(tex, texCoords).r * color;
}
