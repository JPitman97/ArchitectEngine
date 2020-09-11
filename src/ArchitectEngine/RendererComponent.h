#ifndef _RENDERERCOMPONENT_H
#define _RENDERERCOMPONENT_H

#include "Component.h"
#include <string>
#include <glad/glad.h>

class VertexArray;
class VertexBuffer;
class Texture;
class ShaderProgram;

///This class handles rendering of objects.
///
///This class handles the rendering of objects with custom shaders or meshes.
class RendererComponent : public Component
{
public:
	///This method draws the object.
	///
	///This method draws the object each tick, using the shaderprograms draw method.
	void onDisplay() override;

	///This method sets the shader.
	///
	///This method sets the shader for the current object to use when rendering.
	///@param _vert This is the new vertex shader
	///@param _frag This is the new frag shader
	void setShader(const std::string& _vert, const std::string& _frag);
	///This method retrieves the shader.
	///
	///This method returns the shader.
	std::shared_ptr<ShaderProgram> getShader() const { return shader; }
	///This method sets the mesh and texture.
	///
	///This method sets the mesh and texture to the passed in values.
	///@param _path This is the path to the model
	///@param _texPath This is the path to the texture
	void setMesh(const std::string& _path, const std::string& _texPath);
	///This method returns the mesh.
	///
	///This method returns the mesh object.
	std::shared_ptr<VertexArray> getMesh() const { return mesh; }

	std::shared_ptr<VertexBuffer> getobjPositions() const { return objPositions; }
	///This method gets the texture.
	///
	///This method gets the texture and returns it.
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