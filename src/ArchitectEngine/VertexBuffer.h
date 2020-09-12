#ifndef _VERTEXBUFFER_H
#define _VERTEXBUFFER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

///Vertex Buffer class which handles GLfloat data and Id's.
///
///This class handles the creation of model vertex data and passes their vertex information to the shader program.
class VertexBuffer
{
private:
	GLuint id;
	int components;
	std::vector<GLfloat> data;
	bool dirty;

public:
	///Vertex Buffer Constructor
	///
	///This constructor generates the buffers and stores the Id, it also initialise's the components and dirty members. 
	VertexBuffer();

	///Vertex Buffer add method for vec2's
	///
	///This method handles pushing back passed in data to the data member, it also sets the components to 2 and enables dirty.
	///@param _value This parameter contains vertex information for the  position, normal or colour
	void add(const glm::vec2& _value);
	///Vertex Buffer add method for vec3's
	///
	///This method handles pushing back passed in data to the data member, it also sets the components to 3 and enables dirty.
	///@param _value This parameter contains vertex information for the  position, normal and colour
	void add(const glm::vec3& _value);
	///Vertex Buffer add method for vec4's
	///
	///This method handles pushing back passed in data to the data member, it also sets the components to 3 and enables dirty.
	///@param _value This parameter contains vertex information for the  position, normal and colour and extra
	void add(const glm::vec4& _value);

	///Get's the components from the object
	///
	///This method handles retrieving the components for the object instance
	int GetComponents() const;
	///Get's the data size from the object
	///
	///This method handles retrieving the data size for the object instance
	int GetDataSize() const;
	///Get's the Id from the object
	///
	///This method handles retrieving the Id for the object instance
	GLuint GetId();

	std::vector<float> GetData();
};
#endif