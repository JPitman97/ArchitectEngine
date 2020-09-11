#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>

///Transform class.
///
///This class handles the transformations of objects and is used within the TransformComponent.
class Transform
{
public:
	Transform();
	~Transform();

public:
	///This method updates the model matrix of the current object.
	///
	///This method specifies a new model matrix.
	///@param _matrix This is the matrix to be modified and returned
	///@param _position This is the new position for the model
	///@param _rotation This is the new rotation for the model
	///@param _scale This is the new scale for the model
	glm::mat4 updateModelMatrix(glm::mat4& _matrix, const glm::vec3& _position, const glm::vec3& _rotation, const glm::vec3& _scale) const;

	///This method updates the view matrix of the current object.
	///
	///This method specifies a new view matrix.
	///@param _matrix This is the matrix to be modified and returned
	///@param _position This is the new position for the model
	///@param _rotation This is the new rotation for the model
	///@param _deltaTime This is the deltaTime speed for the model
	glm::mat4 updateViewMatrix(glm::mat4& _matrix, glm::vec3& _position, glm::vec3& _rotation, float _deltaTime) const;

	///This method gets the forward vector for the object.
	///
	///This method specifies a new forward vector.
	///@param _direction This is the direction of the vector to calculate
	///@param _rotation This is the rotation for the vector to calculate 
	glm::vec3 getFwd(const glm::vec3& _direction, const glm::vec3& _rotation) const;

	///This method sets the model matrix of the current object.
	///
	///This method specifies a new model matrix.
	///@param _modelMatrix This is the matrix to be set
	void setModelMatrix(glm::mat4 _modelMatrix);

private:
	glm::vec3 fwd;
	glm::mat4 modelMatrix;
};

#endif
