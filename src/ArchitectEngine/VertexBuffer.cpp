#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	try
	{
		if (this != nullptr)
		{
			components = 0;
			dirty = false;

			glGenBuffers(1, &id);

			if (!id)
				std::cout << "ERROR::VertexBuffer::BAD_ID" << std::endl;
		}
		else { throw std::exception("Failed to initialise the VertexBuffer, are models correctly loaded?"); }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void VertexBuffer::add(const glm::vec2& _value)
{
	try
	{
		if (this != nullptr)
		{
			if (components != 2 && components != 0)
				std::cout << "ERROR::VertexBuffer::VEC2::COMPONENTS_NOT_0_OR_2" << std::endl;

			data.push_back(_value.x);
			data.push_back(_value.y);
			components = 2;
			dirty = true;
		}
		else { throw std::exception("Failed to add to the VertexBuffer, are models correctly loaded?"); }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void VertexBuffer::add(const glm::vec3& _value)
{
	try
	{
		if (this != nullptr)
		{
			if (components != 3 && components != 0)
				std::cout << "ERROR::VertexBuffer::VEC2::COMPONENTS_NOT_0_OR_3" << std::endl;

			data.push_back(_value.x);
			data.push_back(_value.y);
			data.push_back(_value.z);
			components = 3;
			dirty = true;
		}
		else { throw std::exception("Failed to add to the VertexBuffer, are models correctly loaded?"); }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void VertexBuffer::add(const glm::vec4& _value)
{
	try
	{
		if (this != nullptr)
		{
			if (components != 4 && components != 0)
				std::cout << "ERROR::VertexBuffer::VEC2::COMPONENTS_NOT_0_OR_4" << std::endl;

			data.push_back(_value.x);
			data.push_back(_value.y);
			data.push_back(_value.z);
			data.push_back(_value.w);
			components = 4;
			dirty = true;
		}
		else { throw std::exception("Failed to add to the VertexBuffer, are models correctly loaded?"); }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

int VertexBuffer::GetComponents() const
{
	try
	{
		if (this != nullptr)
		{
			return components;
		}
		else { throw std::exception("Failed to return components for the VertexBuffer, are models correctly loaded?"); }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

int VertexBuffer::GetDataSize() const
{
	try
	{
		if (this != nullptr)
		{
			return data.size();
		}
		else { throw std::exception("Failed to return data for the VertexBuffer, are models correctly loaded?"); }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

GLuint VertexBuffer::GetId()
{
	try
	{
		if (this != nullptr)
		{
			if (dirty)
			{
				glBindBuffer(GL_ARRAY_BUFFER, id);
				glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data.at(0), GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				dirty = false;
			}

			return id;
		}
		else { throw std::exception("Failed to return id for the VertexBuffer, are models correctly loaded?"); }
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}

std::vector<float> VertexBuffer::GetData()
{
	return data;
}