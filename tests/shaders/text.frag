#version 330 core
out vec4 FragColor;

in vec2 texCoords;
in vec4 texColor;

uniform sampler2D atlas;

void main() {
    float alpha = texture(atlas, texCoords).r;
    FragColor = texColor * alpha;
}
