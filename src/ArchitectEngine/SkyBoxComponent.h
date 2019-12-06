#ifndef _SKYBOXCOMPONENT_H
#define _SKYBOXCOMPONENT_H
#include "Component.h"
#include <GL/glew.h>
#include <vector>

class Texture;
class SkyBloxComponent : public Component
{
public:
	SkyBloxComponent() = default;
	SkyBloxComponent(std::string _fileLoc);

	void onDisplay() override;

private:
	std::vector<GLfloat> skyboxVertices;
	GLuint skyboxVAO, skyboxVBO;
	std::shared_ptr<Texture> texture;
	GLuint cubemapTexture;
};

#endif
