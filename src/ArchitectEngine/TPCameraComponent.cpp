#include "TPCameraComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "RendererComponent.h"
#include "Core.h"
#include "ShaderProgram.h"

void TPCameraComponent::initialise()
{
	camera = getEntity()->getCore()->getCamera();
}

void TPCameraComponent::onTick()
{
	glm::vec3 position = getEntity()->getComponent<TransformComponent>()->getPos();
	position.z += 0.0;
	position.x += 0.3;
	position.y += 0.2;

	camera->setPosition(position);
	getEntity()->getCore()->setCamera(camera);
}
