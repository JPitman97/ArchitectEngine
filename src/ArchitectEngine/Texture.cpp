#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "Texture.h"

Texture::Texture() = default;

GLuint Texture::loadTexture(const std::string& _path)
{
	//Load in a texture and set it correct for OpenGL
	stbi_set_flip_vertically_on_load(true);

	int w;
	int h;
	int chan;
	GLuint id;
	unsigned char* data = stbi_load(_path.c_str(), &w, &h, &chan, 4);
	if (!data)
	{
		throw std::runtime_error("Failed to load texture");
	}

	glGenTextures(1, &id);
	if (!id)
	{
		throw std::runtime_error("Failed to generate OpenGL texture");
	}
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}


Texture::~Texture() = default;
