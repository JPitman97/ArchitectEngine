#include "InputComponent.h"
#include "Entity.h"
#include "Core.h"
#include "Input.h"
#include "TransformComponent.h"
#include "Time.h"

void InputComponent::onTick()
{
	if (getEntity()->getCore()->getInput()->isKey('w'))
	{
		auto TC = getEntity()->getComponent<TransformComponent>();
		TC->setPos(glm::vec3(TC->getPos().x, TC->getPos().y, TC->getPos().z - 2 * Time::deltaTime));
	}
	if (getEntity()->getCore()->getInput()->isKey('s'))
	{
		auto TC = getEntity()->getComponent<TransformComponent>();
		TC->setPos(glm::vec3(TC->getPos().x, TC->getPos().y, TC->getPos().z + 2 * Time::deltaTime));
	}
	if (getEntity()->getCore()->getInput()->isKey('a'))
	{
		auto TC = getEntity()->getComponent<TransformComponent>();
		TC->setPos(glm::vec3(TC->getPos().x - 2 * Time::deltaTime, TC->getPos().y, TC->getPos().z));
	}
	if (getEntity()->getCore()->getInput()->isKey('d'))
	{
		auto TC = getEntity()->getComponent<TransformComponent>();
		TC->setPos(glm::vec3(TC->getPos().x + 2 * Time::deltaTime, TC->getPos().y, TC->getPos().z));
	}
}
