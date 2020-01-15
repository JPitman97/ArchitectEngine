#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>


class Transform
{
public:
	Transform();
	~Transform();

public:
	glm::mat4 updateModelMatrix(glm::mat4& _matrix, const glm::vec3& _position, const glm::vec3& _rotation, const glm::vec3& _scale) const;
	glm::mat4 updateViewMatrix(glm::mat4& _matrix, glm::vec3& _position, glm::vec3& _rotation, float _deltaTime) const;

	void updateInputs(/*Input Params here*/);

	glm::vec3 getFwd(const glm::vec3& _direction, const glm::vec3& _rotation) const;
	void setModelMatrix(glm::mat4 _modelMatrix);

private:
	glm::vec3 fwd;
	glm::mat4 modelMatrix;
};

#endif
