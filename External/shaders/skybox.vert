#version 460

attribute vec3 in_Position;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec3 ex_TexCoord;

void main()
{
	ex_TexCoord = in_Position;
	gl_Position = projectionMatrix * viewMatrix * vec4(in_Position, 1.0);
}