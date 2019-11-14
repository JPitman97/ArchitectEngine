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

class ShaderProgram
{
private:
	GLuint id = 0;
public:
	ShaderProgram();
	ShaderProgram(const std::string& _vert, const std::string& _frag);

	void draw(const std::shared_ptr<VertexArray>& _vertexArray, GLuint _texID);


	void SetUniform(const std::string& _uniform, const glm::vec3& _value);
	void SetUniform(const std::string& _uniform, const glm::vec4& _value);
	void SetUniform(const std::string& _uniform, const glm::mat4& _value);
	void SetUniform(const std::string& _uniform, int _value);


	GLuint GetId() const;
};

#endif
