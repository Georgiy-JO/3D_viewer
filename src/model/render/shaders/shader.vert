#version 330 core                                       // GLSL version
layout(location = 0) in vec3 aPos;                      // position attribute (vec3)
uniform mat4 model;                                     // model matrix uniform
uniform mat4 view;                                      // view (camera) matrix uniform
uniform mat4 projection;                                // projection matrix uniform
void main() {
    // compute clip-space position by multiplying matrices
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //set a constant point size for rendering GL_POINTS
    gl_PointSize = 4.0;
}