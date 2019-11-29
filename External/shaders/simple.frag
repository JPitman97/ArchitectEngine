#version 460

in vec3 in_Color;
uniform sampler2D in_Texture;
varying vec2 ex_TexCoord;

layout(location = 3) out vec4 diffuseColor;

void main()
{
	vec4 tex = texture2D(in_Texture, ex_TexCoord);
	//vec3 color = tex.rgb * in_Color;
	diffuseColor = vec4(1.0,0.0,1.0,1.0);
}