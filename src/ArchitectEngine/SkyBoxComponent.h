#ifndef _SKYBOXCOMPONENT_H
#define _SKYBOXCOMPONENT_H
#include "Component.h"
#include <glad/glad.h>
#include <vector>
#include <string>

class Texture;

///This class handles the skybox.
///
///This class is used to control and render the skybox to the scene.
class SkyBloxComponent : public Component
{
public:
	SkyBloxComponent() = default;

	///This method creates the vertices for the skybox.
	///
	///This method creates the skybox cube along with it's VAO and VBO objects, as well as then loading and saving all texture faces.
	///@param _fileLoc This is the path for the textures
	SkyBloxComponent(const std::string& _fileLoc);

	///This method draws the skybox to the scene.
	///
	///This method takes the loaded textures and renders them to each wall of the cube, as well as modifying the projection matrix.
	void onDisplay() override;

private:
	std::vector<GLfloat> skyboxVertices;
	GLuint skyboxVAO{}, skyboxVBO{};
	std::shared_ptr<Texture> texture;
	GLuint cubemapTexture;
};

#endif
