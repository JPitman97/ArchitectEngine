#version 460

attribute vec3 in_Position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

attribute vec2 in_TexCoord;
varying vec2 ex_TexCoord;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1);
	ex_TexCoord = in_TexCoord;
}