#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <iostream>
#include <GL/glew.h>
#include <vector>


class Texture
{
public:
	Texture();

	GLuint loadTexture(const std::string& _path);
	GLuint loadCubemap(std::vector<std::string> faces);

	~Texture();

private:
	
};

#endif
