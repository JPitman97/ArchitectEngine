#include "TransformComponent.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Core.h"

TransformComponent::TransformComponent()
{
	transform = std::make_shared<Transform>();
}

void TransformComponent::onTick()
{
	//TODO set the objects position and update the shaderprogram uniform "modelMatrix"
	//Move the object in response to input
	glm::mat4 mm = getCore()->getModelMatrix();
	mm = transform->updateModelMatrix(mm, position, rotation, scale);
	getCore()->setModelMatrix(mm);
	getCore()->getShaderProgram()->SetUniform("modelMatrix", mm);
}

void TransformComponent::keyInput()
{
	//Handle key input
}
