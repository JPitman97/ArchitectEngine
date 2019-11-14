#ifndef _CAMERA_H
#define _CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 getViewMatrix() const;
	glm::mat4 setViewMatrix(glm::mat4 _matrix);
	glm::mat4 setPosition(glm::mat4& _matrix, glm::vec3& _position, glm::vec3& _rotation, float _deltaTime);
	glm::vec3 getCamPos() const;
	glm::vec3 getCamRot() const;

private:
	//Initialise the viewMatrix to identity
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	//Define positions for the camera
	glm::vec3 camPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 camRotation = glm::vec3(0.0f, 0.0f, 0.0f);
};

#endif