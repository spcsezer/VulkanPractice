#version 460
layout(location = 0) in vec3 inPos;

layout(set = 0, binding = 0) uniform Camera {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) out vec3 fragDir;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

void main() {
    fragDir = inPos;
    vec4 pos = ubo.proj * ubo.view * vec4(inPos, 1.0);
    gl_Position = pos.xyww;

    /*
    mat4 rotView = mat4(mat3(ubo.view));
    vec4 pos = rotView * vec4(inPos, 0.0);
    fragDir = pos.xyz;
    gl_Position = ubo.proj * vec4(inPos, 1.0);*/
}
