#version 130
attribute vec3 in_Position;

varying vec3 TexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    TexCoords = in_Position;
    vec4 pos = projectionMatrix * viewMatrix * vec4(in_Position, 1.0);
    gl_Position = pos.xyww;
}  
