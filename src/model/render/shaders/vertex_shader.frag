#version 330 core
out vec4 FragColor;                    // color output

uniform vec4 vModelColor;              // color of the model

uniform bool sDottedEdge;              // switch from solid to dotted edges
uniform bool sCircleVertex;            // swtich from square to circle vetrices


void main() {
    //----- Vertices circle drawing -----
    if(sCircleVertex){
        // Calculation: 1. put coordinates in the middle 1x1 square point
        //              2. discard everything outside half square side radious 
        vec2 centered = gl_PointCoord - vec2(0.5);
        if(length(centered)> 0.5){
            discard;
        }
    }

    FragColor = vModelColor;
}