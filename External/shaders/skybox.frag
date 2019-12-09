#version 460

in vec3 ex_TexCoord; // direction vector representing a 3D texture coordinate
uniform samplerCube skybox; // cubemap texture sampler

void main()
{             
	gl_FragColor = texture(skybox, ex_TexCoord);
} 