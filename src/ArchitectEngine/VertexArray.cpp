#include "VertexArray.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	try
	{
		if (this != nullptr)
		{
			dirty = false;

			buffers.resize(10);

			glGenVertexArrays(1, &id);

			if (!id)
				std::cout << "ERROR::VertexArray::BAD_ID" << std::endl;
		}
		else { throw std::exception("Failed to initialise VertexArray, are models correctly loaded?"); }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

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
	try
	{
		if (this != nullptr)
		{
			if (!buffers.at(0))
			{
				std::cout << "ERROR::VertexArray::ERROR_GETTING_VERTEX_COUNT" << std::endl;
			}

			return buffers.at(0)->GetDataSize() / buffers.at(0)->GetComponents();
		}
		else { throw std::exception("Failed to get vertex count, are models correctly loaded?"); }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

GLuint VertexArray::GetId()
{
	try
	{
		if (this != nullptr)
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
		else { throw std::exception("Failed to get VertexArray information, are you sure meshes were loaded correctly?"); }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}