#version 130

uniform sampler2D in_Texture;
varying vec2 ex_TexCoord;

void main()
{
	vec4 tex = texture2D(in_Texture, ex_TexCoord);
	gl_FragColor = vec4(1.0 - tex.r, 1.0 - tex.g, 1.0 - tex.b, 1);
}