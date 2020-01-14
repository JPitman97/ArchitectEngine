#include "VertexArray.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	dirty = false;

	buffers.resize(10);

	glGenVertexArrays(1, &id);

	if (!id)
		std::cout << "ERROR::VertexArray::BAD_ID" << std::endl;
}

void VertexArray::SetBuffer(const std::string& _attribute, const std::shared_ptr<VertexBuffer>& _buffer)
{
	if (_attribute == "in_Position")
	{
		buffers.at(0) = _buffer;
	}
	else if (_attribute == "in_Normal")
	{
		buffers.at(1) = _buffer;
	}
	else if (_attribute == "in_TexCoord")
	{
		buffers.at(2) = _buffer;
	}
	else
	{
		std::cout << "Error sorting Attributes" << std::endl;
	}
	dirty = true;
}

int VertexArray::GetVertexCount()
{
	if (!buffers.at(0))
	{
		std::cout << "ERROR::VertexArray::ERROR_GETTING_VERTEX_COUNT" << std::endl;
	}

	return buffers.at(0)->GetDataSize() / buffers.at(0)->GetComponents();
}

GLuint VertexArray::GetId()
{
	if (dirty)
	{
		glBindVertexArray(id);

		for (int i = 0; i < buffers.size(); i++)
		{
			if (buffers.at(i))
			{
				glBindBuffer(GL_ARRAY_BUFFER, buffers.at(i)->GetId());
				glVertexAttribPointer(i,
					buffers.at(i)->GetComponents(), GL_FLOAT, GL_FALSE,
					buffers.at(i)->GetComponents() * sizeof(GLfloat), static_cast<void*>(nullptr));
				glEnableVertexAttribArray(i);
			}
		}
	}

	return id;
}