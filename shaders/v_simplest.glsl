#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

//Atrybuty
layout (location = 0) in vec4 vertex; 
layout (location = 1) in vec4 normal; 
layout (location = 2) in vec2 texCoord0;

//Zmienne interpolowane
out vec4 l;
out vec4 n;
out vec4 v;
out vec2 iTexCoord0; 

void main(void) {
    vec4 lp = vec4(10, 10, -6, 1); 
    l = normalize(V * lp - V*M*vertex); 
    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); 
    n = normalize(V * M * normal); 
    
    iTexCoord0 = texCoord0;
    
    gl_Position=P*V*M*vertex;
}
