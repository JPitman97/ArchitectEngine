#ifndef _CAMERA_H
#define _CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float ZOOM = 45.0f;

///This class was copied from LearnOpenGL.com with changes to strip unnecessary things for the engine.
///
///This class handles the view matrix, position and lookAt vectors.
class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float Zoom;
	// Camera options
	float MovementSpeed = 1.5f;
	float MouseSensitivity = 0.1f;

	///This constructor sets the position and other values for the camera.
	///
	///This constructor takes a position, up vector as well as a yaw and pitch, these are used to generate the lookAt matrix.
	///@param position This is the position to set the camera.
	///@param up This is the up vector of the camera.
	///@param yaw This is the swivel value of the camera.
	///@param pitch This is the vertical value of the camera.
	Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

	///This constructor sets the position and other values for the camera.
	///
	///This constructor takes a position, up vector as well as a yaw and pitch, these are used to generate the lookAt matrix.
	///@param posX This is the position.x to set the camera.
	///@param posY This is the position.y to set the camera.
	///@param posZ This is the position.z to set the camera.
	///@param upX This is the up.x to set the camera.
	///@param upY This is the up.y to set the camera.
	///@param upZ This is the up.z to set the camera.
	///@param yaw This is the yaw value for the camera.
	///@param pitch This is the vertical value of the camera.
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	///This method returns the view matrix.
	///
	///This method returns the camera View Matrix.
	glm::mat4 getViewMatrix() const;

	///This method sets the camera position.
	///
	///This method takes a position and sets it to the camera.
	///@param _position This is the position to set the camera.
	void setPosition(glm::vec3 _position);

	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);

private:
	///This method updates the lookAt matrix.
	///
	///This method updates the lookAt matrix for movement.

	void updateCameraVectors();
};


#endif