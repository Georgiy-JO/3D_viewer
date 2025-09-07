#version 330 core
out vec4 FragColor;                    // color output

uniform vec4 vModelColor;              // color of the model

uniform bool sDottedEdge;              // switch from solid to dotted edges
uniform bool sCircleVertex;            // swtich from square to circle vetrices


void main() {
    if(sDottedEdge){
        if(int(gl_FragCoord.x + gl_FragCoord.y) % 10 < 5){
            discard;
        }
    }
    FragColor = vModelColor;
}