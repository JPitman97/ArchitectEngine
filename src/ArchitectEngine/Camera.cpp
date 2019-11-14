#include "Camera.h"

Camera::Camera() = default;


Camera::~Camera() = default;

glm::mat4 Camera::getViewMatrix() const
{
	return viewMatrix;
}

glm::mat4 Camera::setViewMatrix(glm::mat4 _matrix)
{
	viewMatrix = std::move(_matrix);
	return viewMatrix;
}

glm::mat4 Camera::setPosition(glm::mat4& _matrix, glm::vec3& _position, glm::vec3& _rotation, float _deltaTime)
{
	//Set the position of the camera
	camPosition = _position;
	_matrix = glm::mat4(1.0f);
	_matrix = glm::translate(_matrix, _position);
	_matrix = glm::rotate(_matrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	_matrix = glm::rotate(_matrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	_matrix = glm::rotate(_matrix, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	return _matrix;
}

glm::vec3 Camera::getCamPos() const
{
	return camPosition;
}

glm::vec3 Camera::getCamRot() const
{
	return camRotation;
}
