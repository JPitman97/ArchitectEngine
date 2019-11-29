#include "ShaderProgram.h"
#include "VertexArray.h"

ShaderProgram::ShaderProgram()
{
	std::string vertShader;
	std::string fragShader;

	std::ifstream file("shaders/simple.vert");

	if (!file.is_open())
	{
		std::cout << "Error" << std::endl;
	}
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			vertShader += line + "\n";
		}
	}
	file.close();

	file.open("shaders/simple.frag");

	if (!file.is_open())
	{
		std::cout << "Error" << std::endl;
	}
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			fragShader += line + "\n";
		}
	}
	file.close();

	const char* vertex = vertShader.c_str();
	const char* fragment = fragShader.c_str();

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertex, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &errorLog[0]);
		std::cout << &errorLog.at(0) << std::endl;
		throw std::exception();
	}

	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragment, NULL);
	glCompileShader(fragmentShaderId);
	success = 0;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &errorLog[0]);
		std::cout << &errorLog.at(0) << std::endl;
		throw std::exception();
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShaderId);
	glAttachShader(id, fragmentShaderId);

	glBindAttribLocation(id, 0, "in_Position");
	glBindAttribLocation(id, 1, "in_Color");
	glBindAttribLocation(id, 2, "in_TexCoord");
	glBindAttribLocation(id, 3, "in_lightColor");

	glLinkProgram(id);
	success = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::cout << "Error" << std::endl;
	}

	glDetachShader(id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

ShaderProgram::ShaderProgram(const std::string& _vert, const std::string& _frag)
{
	std::string vertShader;
	std::string fragShader;

	std::ifstream file(_vert);

	if (!file.is_open())
	{
		std::cout << "Error" << std::endl;
	}
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			vertShader += line + "\n";
		}
	}
	file.close();

	file.open(_frag);

	if (!file.is_open())
	{
		std::cout << "Error" << std::endl;
	}
	else
	{
		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);
			fragShader += line + "\n";
		}
	}
	file.close();

	const char* vertex = vertShader.c_str();
	const char* fragment = fragShader.c_str();

	const GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertex, NULL);
	glCompileShader(vertexShaderId);
	GLint success = 0;
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &errorLog[0]);
		for (auto& i : errorLog)
			std::cout << i;
		std::cout << "Error" << std::endl;
	}

	const GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragment, NULL);
	glCompileShader(fragmentShaderId);
	success = 0;
	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &errorLog[0]);
		for (auto& i : errorLog)
			std::cout << i;
		std::cout << "Error" << std::endl;
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShaderId);
	glAttachShader(id, fragmentShaderId);

	glBindAttribLocation(id, 0, "in_Position");
	glBindAttribLocation(id, 1, "in_Color");
	glBindAttribLocation(id, 2, "in_TexCoord");
	glBindFragDataLocation(id, 3, "diffuseColor");
	//glBindAttribLocation(id, 3, "in_lightColor");
	glLinkProgram(id);
	success = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::cout << "Error" << std::endl;
	}

	glDetachShader(id, vertexShaderId);
	glDeleteShader(vertexShaderId);
	glDetachShader(id, fragmentShaderId);
	glDeleteShader(fragmentShaderId);
}

void ShaderProgram::draw(const std::shared_ptr<VertexArray>& _vertexArray, GLuint _texID)
{
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LEQUAL);

	//Cull faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glBindTexture(GL_TEXTURE_2D, _texID);
	glUseProgram(id);
	glBindVertexArray(_vertexArray->GetId());
	glDrawArrays(GL_TRIANGLES, 0, _vertexArray->GetVertexCount());
	glBindVertexArray(0);
	glUseProgram(0);
}

void ShaderProgram::SetUniform(const std::string& _uniform, const glm::vec3& _value)
{
	const GLuint uniformId = glGetUniformLocation(id, _uniform.c_str());

	if (uniformId == -1)
	{
		std::cout << "Error" << std::endl;
	}

	glUseProgram(id);
	glUniform3f(uniformId, _value.x, _value.y, _value.z);
	glUseProgram(0);
}

void ShaderProgram::SetUniform(const std::string& _uniform, const glm::vec4& _value)
{
	const GLuint uniformId = glGetUniformLocation(id, _uniform.c_str());

	if (uniformId == -1)
	{
		std::cout << "Error" << std::endl;
	}

	glUseProgram(id);
	glUniform4f(uniformId, _value.x, _value.y, _value.z, _value.w);
	glUseProgram(0);
}

void ShaderProgram::SetUniform(const std::string& _uniform, const glm::mat4& _value)
{
	const GLuint uniformId = glGetUniformLocation(id, _uniform.c_str());

	if (uniformId == -1)
	{
		std::cout << "Error" << std::endl;
	}

	glUseProgram(id);
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(_value));
	glUseProgram(0);
}

void ShaderProgram::SetUniform(const std::string& _uniform, const int _value)
{
	const GLuint uniformId = glGetUniformLocation(id, _uniform.c_str());

	if (uniformId == -1)
	{
		std::cout << "Error" << std::endl;
	}

	glUseProgram(id);
	glUniform1f(uniformId, _value);
	glUseProgram(0);
}

GLuint ShaderProgram::GetId() const
{
	return id;
}
