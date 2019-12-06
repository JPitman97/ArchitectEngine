#version 460

attribute vec3 in_Position;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec3 ex_TexCoord;

void main()
{
vec4 pos = projectionMatrix * viewMatrix * vec4(in_Position, 1);
	gl_Position = pos.xyww;
	ex_TexCoord = in_Position;
}