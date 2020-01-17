#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <iostream>
#include <GL/glew.h>
#include <vector>

///This class handles texture loading.
///
///This class handles the loading of textures as well as cubemaps.
class Texture
{
public:

	Texture();

	///This method loads a texture from a defined path.
	///
	///This method takes a path and loads the texture from there, as well as setting parameters such as tiling.
	///@param _path This is the path for the texture
	GLuint loadTexture(const std::string& _path);
	///This method loads a cubemap from a defined path.
	///
	///This method takes a path and loads the cubemap from there, as well as setting parameters such as tiling.
	///@param _faces This is the path for the cubemap texture faces
	GLuint loadCubemap(std::vector<std::string> faces);

	~Texture();

private:
	
};

#endif
