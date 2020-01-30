#include "InputComponent.h"
#include "Entity.h"
#include "Core.h"
#include "Input.h"
#include "TransformComponent.h"
#include "Time.h"
#include "Camera.h"

void InputComponent::onTick()
{
	const float velocity = 2 * Time::deltaTime;
	const auto camera = getEntity()->getCore()->getCamera();
	auto TC = getEntity()->getComponent<TransformComponent>();

	TC->setRot(glm::vec3(0, -90.0f - camera->Yaw, camera->Front.z));

	if (getEntity()->getCore()->getInput()->isKey('W'))
	{
		TC->setPos(TC->getPos() += camera->Front * velocity);
	}
	if (getEntity()->getCore()->getInput()->isKey('S'))
	{
		TC->setPos(TC->getPos() -= camera->Front * velocity);
	}
	if (getEntity()->getCore()->getInput()->isKey('A'))
	{
		TC->setPos(TC->getPos() -= camera->Right * velocity);
	}
	if (getEntity()->getCore()->getInput()->isKey('D'))
	{
		TC->setPos(TC->getPos() += camera->Right * velocity);
	}
}
