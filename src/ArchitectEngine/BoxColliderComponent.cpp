#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "Core.h"
#include <iostream>
#include "AudioComponent.h"

void BoxColliderComponent::onTick()
{
	//Fix this function
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
				//this->getEntity()->getComponent<AudioComponent>()->playAudio("Assets/dixie_horn.ogg");

				return true;
			}
		}
	}
	return false;
}

glm::vec3 BoxColliderComponent::getCollisionResponse(const glm::vec3& _position, const glm::vec3& _size) const
{
	return glm::vec3{ 0 }; //Fix this function
}