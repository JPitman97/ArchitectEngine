#include "SkyBoxComponent.h"
#include "Texture.h"
#include "TransformComponent.h"
#include "RendererComponent.h"
#include "ShaderProgram.h"
#include "Entity.h"

SkyBloxComponent::SkyBloxComponent(std::string _fileLoc)
{
	skyboxVertices = {
		// Positions
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	// Setup skybox VAO
	
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	// Cubemap (Skybox)
	std::vector<const GLchar*> faces;
	std::string right = _fileLoc + "/right.tga";
	std::string left = _fileLoc + "/left.tga";
	std::string top = _fileLoc + "/top.tga";
	std::string bottom = _fileLoc + "/bottom.tga";
	std::string back = _fileLoc + "/back.tga";
	std::string front = _fileLoc + "/front.tga";

	faces.push_back(right.c_str());
	faces.push_back(left.c_str());
	faces.push_back(top.c_str());
	faces.push_back(bottom.c_str());
	faces.push_back(back.c_str());
	faces.push_back(front.c_str());
	cubemapTexture = texture->loadCubemap(faces);
}

void SkyBloxComponent::onDisplay()
{
	// Draw skybox as last
	glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
	auto view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2));	// Remove any translation component of the view matrix
	auto projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(getEntity()->getComponent<RendererComponent>()->getShader()->GetId(), "viewMatrix"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(getEntity()->getComponent<RendererComponent>()->getShader()->GetId(), "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));

	// skybox cube
	glBindVertexArray(skyboxVAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // Set depth function back to default
}
