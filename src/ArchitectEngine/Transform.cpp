#include "Transform.h"

Transform::Transform() = default;

glm::mat4 Transform::updateModelMatrix(glm::mat4& _matrix, const glm::vec3& _position, const glm::vec3& _rotation, const glm::vec3& _scale) const
//ModelMatrix
{
	//Handle movement of objects
	_matrix = glm::mat4(1.0f);
	_matrix = glm::translate(_matrix, _position);
	_matrix = glm::rotate(_matrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	_matrix = glm::rotate(_matrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	_matrix = glm::rotate(_matrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	_matrix = glm::scale(_matrix, _scale);
	return _matrix;
}

glm::mat4 Transform::updateViewMatrix(glm::mat4& _matrix, glm::vec3& _position, glm::vec3& _rotation, float _deltaTime) const
{
	//Handle movement of the camera
	glm::mat4 t(1.0f);
	t = glm::translate(t, glm::vec3(0, 0, 0));                    // move forward 1 unit
	t = glm::rotate(t, glm::radians(_rotation.y), glm::vec3(0, 1, 0)); // rotate it by yAngle

	_matrix = glm::mat4(1.0f);
	_matrix = glm::translate(_matrix, _position);
	_matrix = glm::rotate(_matrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

	return _matrix;
}
//Pass in the camera view matrix, NOT the model, move the camera and set the player position equal to the camera position
void Transform::updateInputs() {

	//TODO Handle inputs here
}

glm::vec3 Transform::getFwd(const glm::vec3& _direction, const glm::vec3& _rotation) const
{
	glm::mat4 t(1.0f);                                            // create arbitary matrix

	t = glm::rotate(t, glm::radians(_rotation.y), glm::vec3(0, 1, 0)); // rotate it by yAngle
	t = glm::translate(t, _direction);                    // move forward 1 unit
	glm::vec3 fwd = t * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);        // apply to an initial position
	fwd = glm::normalize(fwd);

	return fwd;
}

void Transform::setModelMatrix(glm::mat4 _modelMatrix)
{
	modelMatrix = _modelMatrix;
}

Transform::~Transform() = default;
