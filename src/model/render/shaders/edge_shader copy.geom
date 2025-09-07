#version 330 core
layout(lines) in;
layout(triangle_strip, max_vertices = 4) out;

uniform float dEdgeWidth;       //width of line
uniform mat4 mProjection;       //projection matrix uniform

uniform vec2 uViewspace;    // (width, height) in pixels

out vec2 fs_uv;            // for your fragment shader AA, etc.

void main() {
    // clip-space input
    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;

    // 1) clip -> NDC (range -1..1)
    vec2 ndc0 = p0.xy / p0.w;
    vec2 ndc1 = p1.xy / p1.w;

    // 2) NDC -> screen pixels (0..width, 0..height)
    vec2 sp0 = (ndc0 * 0.5 + 0.5) * uViewspace;
    vec2 sp1 = (ndc1 * 0.5 + 0.5) * uViewspace;

    // 3) compute perp in pixel space
    vec2 dir = sp1 - sp0;
    float len = length(dir);
    vec2 dirN = (len < 1e-6) ? vec2(0.0, 1.0) : dir / len;
    vec2 perp = vec2(-dirN.y, dirN.x);

    // 4) offset in pixels (half width)
    vec2 offset = perp * (dEdgeWidth * 0.5);

    // 5) build quad corners in pixel space
    vec2 s0 = sp0 + offset;
    vec2 s1 = sp0 - offset;
    vec2 s2 = sp1 + offset;
    vec2 s3 = sp1 - offset;

    // 6) back to NDC
    vec2 ndc_s0 = (s0 / uViewspace - 0.5) * 2.0;
    vec2 ndc_s1 = (s1 / uViewspace - 0.5) * 2.0;
    vec2 ndc_s2 = (s2 / uViewspace - 0.5) * 2.0;
    vec2 ndc_s3 = (s3 / uViewspace - 0.5) * 2.0;

    // 7) reconstruct clip-space: ndc * original_w
    //    Preserve z and w from the original vertex so depth behaves correctly.
    gl_Position = vec4(ndc_s0 * p0.w, p0.z, p0.w);
    fs_uv = vec2(0.0, 0.0);
    EmitVertex();

    gl_Position = vec4(ndc_s1 * p0.w, p0.z, p0.w);
    fs_uv = vec2(0.0, 1.0);
    EmitVertex();

    gl_Position = vec4(ndc_s2 * p1.w, p1.z, p1.w);
    fs_uv = vec2(1.0, 0.0);
    EmitVertex();

    gl_Position = vec4(ndc_s3 * p1.w, p1.z, p1.w);
    fs_uv = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

