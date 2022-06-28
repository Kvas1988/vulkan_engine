#version 450

layout(location = 0) in vec2 position;

void main() {
    // gl_VertexIndex - index of verticies which is handled now
    gl_Position = vec4(position, 0.0, 1.0); 
}