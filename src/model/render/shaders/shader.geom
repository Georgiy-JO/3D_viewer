#version 330 core
layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

uniform float dEdgeWidth;       //width of line
uniform mat4 mProjection;       //projection matrix uniform

void main() {
    vec4 p0 = gl_in[0].gl_Position; // first vertex of the line
    vec4 p1 = gl_in[1].gl_Position; // second vertex of the line
    //normalize
    vec2 p0n = p0.xy / p0.w;
    vec2 p1n = p1.xy / p1.w;

    vec2 dir = normalize(p1n - p0n);         //directional vector len=1
    vec2 normal = vec2(-dir.y, dir.x) * dEdgeWidth * 0.5;   //normal vect

    gl_Position = (p0 + vec4(normal, 0, 0)); EmitVertex();
    gl_Position = (p0 - vec4(normal, 0, 0)); EmitVertex();
    gl_Position = (p1 + vec4(normal, 0, 0)); EmitVertex();
    gl_Position = (p1 - vec4(normal, 0, 0)); EmitVertex();

    EndPrimitive();
}


