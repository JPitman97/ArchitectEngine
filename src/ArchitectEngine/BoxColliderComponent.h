#ifndef _BOXCOLLIDERCOMPONENT_H
#define _BOXCOLLIDERCOMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class BoxColliderComponent : public Component
{
public:

	void onTick() override;
	void setSize(const glm::vec3& _size);
	glm::vec3 getSize() const;
	void setOffset(const glm::vec3& _offset);
	glm::vec3 getOffset() const;

private:
	glm::vec3 size;
	glm::vec3 offset;

	bool isColliding(const glm::vec3& _position, const glm::vec3& _size) const;
	glm::vec3 getCollisionResponse(const glm::vec3& _position, const glm::vec3& _size) const;
};

inline glm::vec3 BoxColliderComponent::getSize() const
{
	return size;
}

#endif
