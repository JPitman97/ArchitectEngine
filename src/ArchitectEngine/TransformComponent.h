#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class Transform;

class TransformComponent : public Component
{
public:
	TransformComponent();

	void onTick() override;

	void keyInput();

	void setPos(const glm::vec3& _pos) { position = _pos; }
	glm::vec3 getPos() { return position; }
	void setRot(const glm::vec3& _rot) { rotation = _rot; }
	glm::vec3 getRot() { return rotation; }
	void setScale(const glm::vec3& _scale) { scale = _scale; }
	glm::vec3 getScale() const { return scale; }

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	std::shared_ptr<Transform> transform;
};

#endif
