#version 460

in vec3 in_Color;
uniform sampler2D in_Texture;
varying vec2 ex_TexCoord;

out vec4 diffuseColor;

void main()
{
	vec4 tex = texture2D(in_Texture, ex_TexCoord);
	diffuseColor = tex;
}