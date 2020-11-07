#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aCoords;
// 0 = frame index
// 1 = time started
layout (location = 2) in vec3 meta;

out vec2 texCoords;
out vec4 texColor;

uniform float currentTime;

// 4 vertices for each frame
#define COLLECTIVE_MAX_FRAMES (4 * 512)
struct Frame {
    float animationTime;
    float switchTime;
    vec2 texCoords;
    int nextFrame;
    float PADDING;
};
layout (std140) uniform DANZUN_ANIMATIONS {
    Frame frames[COLLECTIVE_MAX_FRAMES];
};

void main() {
    gl_Position = vec4(aPos, 0, 1);

    Frame &f = frames[round(meta.a)];

    float timePos = (currentTime - meta.b) % f.animationTime;

    for () {

    }

    texCoords = aCoords;
    texColor = aColor;
}
