#version 330 core
out vec4 FragColor;                    // color output

uniform vec4 vModelColor;              // color of the model

uniform bool sDottedEdge;              // switch from solid to dotted edges
uniform bool sCircleVertex;            // swtich from square to circle vetrices

in vec2 fs_uv;

uniform vec2 uViewspace; // used to compute AA width in pixels

void main() {
    // fs_uv.y goes 0..1 across the width; center is 0.5
    float distAcross = abs(fs_uv.y - 0.5);
    // convert to pixel-based antialias width
    float aa_pixels = 1.0; // sharpen/soften here
    float halfy = 0.5;
    // compute alpha fading near border
    float alpha = smoothstep(halfy, halfy - (aa_pixels / uViewspace.y), distAcross);
    FragColor = vec4(vModelColor.rgb, vModelColor.a * alpha);
}

