#include "CameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Core.h"
#include "ShaderProgram.h"

CameraComponent::CameraComponent()
{
	camera = std::make_shared<Camera>();
}

//This is the possible cause for the stutter, this runs after setting the new position with inputs
void CameraComponent::Tick(float _DT) const
{
	glm::mat4 matrix = camera->getViewMatrix();
	glm::vec3 position = getEntity()->getComponent<TransformComponent>()->getPos();
	glm::vec3 rotation = getEntity()->getComponent<TransformComponent>()->getRot();
	position.z += 0.5;
	position.y += 0.07;
	rotation.y -= 180;

	const glm::mat4 viewMatrix = camera->setPosition(matrix, position, rotation, _DT);
	getCore()->getShaderProgram()->SetUniform("viewMatrix", glm::inverse(viewMatrix));
}

void CameraComponent::initialise() const
{
	const glm::mat4 viewMatrix = camera->setViewMatrix(glm::mat4(1.0f));
	getCore()->getShaderProgram()->SetUniform("viewMatrix", viewMatrix);
}

CameraComponent::~CameraComponent() = default;
