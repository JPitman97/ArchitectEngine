#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <iostream>
#include <GL/glew.h>


class Texture
{
public:
	Texture();

	GLuint loadTexture(const std::string& _path);

	~Texture();

private:
	
};

#endif
