#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D tex;

void main() {
    // FragColor = texture(tex, texCoords + vec2(0.5) * (1.0 / 400.0));
    FragColor = texture(tex, texCoords);
}
