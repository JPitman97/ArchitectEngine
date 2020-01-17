#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "Core.h"
#include <iostream>
#include "AudioComponent.h"

void BoxColliderComponent::onTick()
{
	for (auto& entity : getEntity()->getCore()->getEntities())
	{
		if (entity->getComponent<BoxColliderComponent>() && this->getEntity() != entity)
		{
			glm::vec3 newPos = getCollisionResponse(entity->getComponent<TransformComponent>()->getPos(), entity->getComponent<BoxColliderComponent>()->getSize());
		}
	}
}

void BoxColliderComponent::setSize(const glm::vec3& _size)
{
	size = _size;
}

void BoxColliderComponent::setOffset(const glm::vec3& _offset)
{
	offset = _offset;
}

glm::vec3 BoxColliderComponent::getOffset() const
{
	return offset;
}

bool BoxColliderComponent::isColliding(const glm::vec3& _position, const glm::vec3& _size) const
{
	// check the X axis
	if (abs(this->getEntity()->getComponent<TransformComponent>()->getPos().x - _position.x) < this->size.x + _size.x)
	{
		//check the Y axis
		if (abs(this->getEntity()->getComponent<TransformComponent>()->getPos().y - _position.y) < this->size.y + _size.y)
		{
			//check the Z axis
			if (abs(this->getEntity()->getComponent<TransformComponent>()->getPos().z - _position.z) < this->size.z + _size.z)
			{
				std::cout << "Collision" << std::endl;
				this->getEntity()->getComponent<AudioComponent>()->playAudio("Assets/dixie_horn.ogg");
				for (auto& entity : getEntity()->getCore()->getEntities())
				{
					if (entity->getComponent<BoxColliderComponent>() && this->getEntity() != entity)
					{
						entity->getComponent<AudioComponent>()->playAudio("Assets/Kryp.ogg");;
					}
				}
				return true;
			}
		}
	}
	return false;
}

glm::vec3 BoxColliderComponent::getCollisionResponse(const glm::vec3& _position, const glm::vec3& _size) const
{
	float amount = 0.1f;
	float step = 0.1f;

	glm::vec3 pos = this->getEntity()->getComponent<TransformComponent>()->getPos();

	while (true)
	{
		if (!isColliding(_position, _size)) {
			break;
		}
		else {
			this->getEntity()->getComponent<TransformComponent>()->setPos(glm::vec3(pos.x += amount, pos.y, pos.z));
		}
		if (!isColliding(_position, _size)) {
			break;
		}
		else {
			this->getEntity()->getComponent<TransformComponent>()->setPos(glm::vec3(pos.x -= (amount * 2), pos.y, pos.z));
		}
		if (!isColliding(_position, _size)) {
			break;
		}
		else
		{
			this->getEntity()->getComponent<TransformComponent>()->setPos(glm::vec3(pos.x += amount, pos.y, pos.z += amount));
		}
		if (!isColliding(_position, _size)) {
			break;
		}
		else {
			this->getEntity()->getComponent<TransformComponent>()->setPos(glm::vec3(pos.x, pos.y, pos.z - (amount * 2)));
		}
		if (!isColliding(_position, _size)) {
			break;
		}
		else {
			amount += step;
		}
	}

	return pos;
}