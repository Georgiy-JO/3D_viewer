#version 330 core                                       // GLSL version
layout(location = 0) in vec3 aPos;                      // position attribute (vec3)

uniform mat4 mTransformation;                            // transformation matrix uniform
uniform mat4 mCamera;                                    // camera matrix uniform
uniform mat4 mProjection;                                // projection matrix uniform

uniform float dVertexSize;                              // verteces size

void main() {
    // compute clip-space position by multiplying matrices
    gl_Position = mProjection * mCamera * mTransformation * vec4(aPos, 1.0);
    gl_PointSize = dVertexSize;
}