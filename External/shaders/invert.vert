#version 130

attribute vec3 in_Position;
attribute vec3 in_Normal;
attribute vec2 in_TexCoord;

varying vec2 ex_TexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1);
	ex_TexCoord = in_TexCoord;
}