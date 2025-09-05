#version 330 core                                       // GLSL version
layout(location = 0) in vec3 aPos;                      // position attribute (vec3)

uniform mat4 transformation;                            // transformation matrix uniform
uniform mat4 camera;                                    // camera matrix uniform
uniform mat4 projection;                                // projection matrix uniform

uniform float vertex_size;                              // verteces size

void main() {
    // compute clip-space position by multiplying matrices
    gl_Position = projection * camera * transformation * vec4(aPos, 1.0);
    gl_PointSize = vertex_size;
}