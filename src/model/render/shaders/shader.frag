#version 330 core
out vec4 FragColor;                    // color output

uniform vec4 model_color;              // color of the model

uniform bool edges_vertex_switch;      // switch from 0 - edges to 1- vertices
uniform bool dotted_edge;              // switch from solid to dotted edges
uniform bool circle_vertex;            // swtich from square to circle vetrices


void main() {
    
    //----- Edges dotted drawing -----
    if(!edges_vertex_switch && dotted_edge){
        if(int(gl_FragCoord.x + gl_FragCoord.y) % 10 < 5){
            discard;
        }
    }

    //----- Vertices circle drawing -----
    if(edges_vertex_switch && circle_vertex){
        // Calculation: 1. put coordinates in the middle 1x1 square point
        //              2. discard everything outside half square side radious 
        if(length(gl_PointCoord-vec2(0.5))>0.5){
            discard;
        }
    }

    FragColor = model_color;
}