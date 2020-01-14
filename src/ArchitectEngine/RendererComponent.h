#ifndef _RENDERERCOMPONENT_H
#define _RENDERERCOMPONENT_H

#include "Component.h"
#include <string>
#include <GL/glew.h>

//class RendererComponent : public Component
//{
//public:
//	RendererComponent();
//
//	void onDisplay() override;
//
//private:
//	unsigned int programId;
//	unsigned int vaoId;
//};

class VertexArray;
class VertexBuffer;
class Texture;
class ShaderProgram;

class RendererComponent : public Component
{
public:

	void onDisplay() override;

	void setShader(const std::string& _vert, const std::string& _frag);
	std::shared_ptr<ShaderProgram> getShader() const { return shader; }
	void setMesh(std::string path, const std::string& texPath);
	std::shared_ptr<VertexArray> getMesh() const { return mesh; }
	GLuint getTex() const { return tex; }

private:
	std::shared_ptr<ShaderProgram> shader;
	std::shared_ptr<VertexBuffer> objPositions;
	std::shared_ptr<VertexBuffer> objNormals;
	std::shared_ptr<VertexBuffer> objTexCoords;
	std::shared_ptr<VertexArray> mesh;
	std::shared_ptr<Texture> texture;
	GLuint tex = 0;
};

#endif