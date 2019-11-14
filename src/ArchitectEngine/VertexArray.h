#ifndef _VERTEXARRAY_H
#define _VERTEXARRAY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class VertexBuffer;

class VertexArray
{

private:
	GLuint id;
	std::vector<std::shared_ptr<VertexBuffer>> buffers;
	bool dirty;

public:
	VertexArray();

	void SetBuffer(const std::string& _attribute, const std::shared_ptr<VertexBuffer>& _buffer);

	int GetVertexCount();
	GLuint GetId();

};
#endif
