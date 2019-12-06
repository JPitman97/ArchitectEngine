#version 460

uniform samplerCube skybox;
varying vec3 ex_TexCoord;

out vec4 diffuseColor;

void main()
{
	vec4 tex = texture(skybox, ex_TexCoord);
	diffuseColor = tex;
}