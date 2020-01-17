#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class Transform;

///This Class handles the transforms of an object.
///
///This class is an abstraction to the Transform class, allowing the user only the necessities.
class TransformComponent : public Component
{
public:
	///This constructor creates a new instance of Transform.
	///
	///This constructor creates an instance of Transform to store and retrieve values from.
	TransformComponent();

	///This method is ran every tick.
	///
	///This method handles the movement of the object and also the creation of new matrices each tick.
	void onTick() override;

	///This method sets the position of the model.
	///
	///This method takes a position and overrides the models position with it.
	///@param _pos This is the new position for the model
	void setPos(const glm::vec3& _pos) { position = _pos; }
	///This method gets the position of the model.
	///
	///This method returns the models position.
	glm::vec3 getPos() { return position; }
	///This method sets the rotation of the model.
	///
	///This method takes a rotation and overrides the models rotation with it.
	///@param _rot This is the new rotation for the model
	void setRot(const glm::vec3& _rot) { rotation = _rot; }
	///This method gets the position of the model.
	///
	///This method gets the rotation of the model and returns it.
	glm::vec3 getRot() { return rotation; }
	///This method sets the scale of the model.
	///
	///This method takes a scale and overrides the models scale with it.
	///@param _scale This is the new scale for the model
	void setScale(const glm::vec3& _scale) { scale = _scale; }
	///This method gets the scale of the model.
	///
	///This method gets the scale of the model and returns it.
	glm::vec3 getScale() const { return scale; }

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	std::shared_ptr<Transform> transform;
};

#endif
