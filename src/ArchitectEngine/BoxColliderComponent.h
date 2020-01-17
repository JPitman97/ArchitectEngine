#ifndef _BOXCOLLIDERCOMPONENT_H
#define _BOXCOLLIDERCOMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

///This class handles AABB collisions between objects.
///
///This class handles checking for collisions as well as allowing for size adjustments to the bounding box.
class BoxColliderComponent : public Component
{
public:
	///This method calls getCollisionResponse with entities each frame.
	///
	///This method checks for collisions from the getCollisionResponse method.
	void onTick() override;
	///This method sets the size of the entity bounding box.
	///
	///This method sets the size of the bounding box on the entity.
	///@param _size This is the size of the Bounding Box
	void setSize(const glm::vec3& _size);
	///This method returns the size of the entity bounding box.
	///
	///This method returns the size of the bounding box on the entity.
	glm::vec3 getSize() const;
	///This method sets the size of the entity offset.
	///
	///This method sets the size of the offset on the entity.
	///@param _offset This is the size of the offset
	void setOffset(const glm::vec3& _offset);
	///This method returns the size of the offset.
	///
	///This method returns the size of the offset on the entity.
	glm::vec3 getOffset() const;

private:
	glm::vec3 size;
	glm::vec3 offset;

	///This method checks to see whether two entities are overlapping.
	///
	///This method checks for collision between two entities.
	///@param _position This is the position of the entity
	///@param _size This is the size of the entities bounding box
	bool isColliding(const glm::vec3& _position, const glm::vec3& _size) const;

	///This method gets the collision response if two objects are colliding.
	///
	///This method pushes two objects away if they collide, to avoid clipping.
	///@param _position This is the position of the entity
	///@param _size This is the size of the bounding box.
	glm::vec3 getCollisionResponse(const glm::vec3& _position, const glm::vec3& _size) const;
};

inline glm::vec3 BoxColliderComponent::getSize() const
{
	return size;
}

#endif
