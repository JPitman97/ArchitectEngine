#ifndef _SHADERPROGRAM_H
#define _SHADERPROGRAM_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "fstream"

class VertexArray;

///This class handles the shaders and uniforms.
///
///This class handles the loading of shaders and also the setting of their uniforms, as well as default drawing.
class ShaderProgram
{
private:
	GLuint id = 0;
public:
	///This constructor loads the two supplied shaders.
	///
	///this constructor loads the two supplied shaders and stores them for use.
	///@param _vert This is the path for the vertex shader
	///@param _frag This is the path to the frag shader
	ShaderProgram(const std::string& _vert, const std::string& _frag);

	///This method handles object rendering.
	///
	///This method uses the default shaders to render an object.
	///@param _vertexArray This is the vertex Array for the mesh
	///@param _texID This is the texture ID of the material
	///@param _id This is used if a new program needs to be used
	void draw(const std::shared_ptr<VertexArray>& _vertexArray, GLuint _texID, GLuint _id = NULL);

	///This method sets the shader uniform.
	///
	///This method sets the shaders uniform to the passed in value.
	///@param _uniform This is the uniform to be set
	///@param _value This is the value to set the uniform too
	void SetUniform(const std::string& _uniform, const glm::vec3& _value);
	///This method sets the shader uniform.
	///
	///This method sets the shaders uniform to the passed in value.
	///@param _uniform This is the uniform to be set
	///@param _value This is the value to set the uniform too
	void SetUniform(const std::string& _uniform, const glm::vec4& _value);
	///This method sets the shader uniform.
	///
	///This method sets the shaders uniform to the passed in value.
	///@param _uniform This is the uniform to be set
	///@param _value This is the value to set the uniform too
	void SetUniform(const std::string& _uniform, const glm::mat4& _value);
	///This method sets the shader uniform.
	///
	///This method sets the shaders uniform to the passed in value.
	///@param _uniform This is the uniform to be set
	///@param _value This is the value to set the uniform too
	void SetUniform(const std::string& _uniform, int _value);

	///This method gets the shader Id.
	///
	///This method gets the shaders Id and returns it.
	GLuint GetId() const;
};

#endif
