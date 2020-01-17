#ifndef _VERTEXARRAY_H
#define _VERTEXARRAY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class VertexBuffer;

///Vertex Array class which handles GLfloat data and Id's.
///
///This class handles the creation of model vertex data and passes their vertex information to the shader program.
class VertexArray
{

private:
	GLuint id;
	std::vector<std::shared_ptr<VertexBuffer>> buffers;
	bool dirty;

public:
	///Vertex Array class which handles GLfloat data and Id's.
	///
	///This constructor handles the resizing of the buffer object as well as the generation of the VertexArray Id.
	VertexArray();

	///Set Buffer method which handles setting attributes. to locations specified in the shader program.
	///
	///Set Buffer method which handles setting attributes to locations specified in the shader program.
	///@param _attribute This is the name of the attribute to assign in the shader
	///@param _buffer This is the information to be stored in the attribute
	void SetBuffer(const std::string& _attribute, const std::shared_ptr<VertexBuffer>& _buffer);

	///Getter method which retrieves the vertex count.
	///
	///This method returns the total vertices of the current mesh.
	int GetVertexCount();

	///Get's the Id of the Vertex Array.
	///
	///This method returns the Id of the Vertex Array.
	GLuint GetId();

};
#endif
