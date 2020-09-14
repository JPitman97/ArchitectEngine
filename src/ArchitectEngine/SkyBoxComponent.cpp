#include "SkyBoxComponent.h"
#include "Texture.h"
#include "TransformComponent.h"
#include "RendererComponent.h"
#include "ShaderProgram.h"
#include "Entity.h"
#include "Core.h"
#include "Camera.h"

SkyBoxComponent::SkyBoxComponent(const std::string& _fileLoc)
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * skyboxVertices.size(), &skyboxVertices.at(0), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glBindVertexArray(0);

	// Cubemap (Skybox)
	std::vector<std::string> faces;
	faces.push_back(_fileLoc + "/right.jpg");
	faces.push_back(_fileLoc + "/left.jpg");
	faces.push_back(_fileLoc + "/top.jpg");
	faces.push_back(_fileLoc + "/bottom.jpg");
	faces.push_back(_fileLoc + "/front.jpg");
	faces.push_back(_fileLoc + "/back.jpg");

	cubemapTexture = texture->loadCubemap(faces);
}

void SkyBoxComponent::onDisplay()
{
	// draw skybox as last
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	auto shader = getEntity()->getComponent<RendererComponent>()->getShader();
	// skybox cube
	glUseProgram(shader->GetId());
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glm::mat4 view = glm::mat4(glm::mat3(getEntity()->getCore()->getCamera()->getViewMatrix())); // remove translation from the view matrix
	shader->SetUniform("viewMatrix", view);
	shader->SetUniform("projectionMatrix", glm::perspective(getEntity()->getCore()->getCamera()->Zoom, (float)getEntity()->getCore()->getScreenSize().x / (float)getEntity()->getCore()->getScreenSize().y, 0.1f, 100.0f));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glUseProgram(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}
