#ifndef _VERTEXBUFFER_H
#define _VERTEXBUFFER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class VertexBuffer
{

private:
	GLuint id;
	int components;
	std::vector<GLfloat> data;
	bool dirty;

public:
	VertexBuffer();

	void add(const glm::vec2& _value);
	void add(const glm::vec3& _value);
	void add(const glm::vec4& _value);

	int GetComponents() const;
	int GetDataSize() const;
	GLuint GetId();


};
#endif
