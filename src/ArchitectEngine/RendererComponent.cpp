#include "RendererComponent.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Core.h"
#include "ObjectLoader.h"
#include "ShaderProgram.h"

void RendererComponent::onDisplay()
{
	if (!shader)
	{
		getCore()->getShaderProgram()->draw(mesh, tex);
	}
	else
	{
		if (mesh && tex)
			shader->draw(mesh, tex, shader->GetId());
	}
}

void RendererComponent::setShader(const std::string & _vert, const std::string & _frag)
{
	shader = std::make_shared<ShaderProgram>(_vert, _frag);
}

void RendererComponent::setMesh(std::string path, const std::string& texPath)
{
	//Set the mesh to the path passed in, then load the texture and apply it together, can be different textures for the same mesh
	objl::Loader loader;
	objl::Mesh curMesh;
	loader.LoadFile(path);
	curMesh = loader.LoadedMeshes[0]; //Crashes program
	objPositions = std::make_shared<VertexBuffer>();
	objNormals = std::make_shared<VertexBuffer>();
	objTexCoords = std::make_shared<VertexBuffer>();
	mesh = std::make_shared<VertexArray>();

	for (auto& vertice : curMesh.Vertices)
	{
		objPositions->add(glm::vec3(vertice.Position.X, vertice.Position.Y, vertice.Position.Z));
	}
	for (auto& vertice : curMesh.Vertices)
	{
		objNormals->add(glm::vec3(vertice.Normal.X, vertice.Normal.Y, vertice.Normal.Z));
	}
	for (auto& vertice : curMesh.Vertices)
	{
		objTexCoords->add(glm::vec2(vertice.TextureCoordinate.X, vertice.TextureCoordinate.Y));
	}

	tex = texture->loadTexture(texPath);

	mesh->SetBuffer("in_Position", objPositions);
	mesh->SetBuffer("in_Normal", objNormals);
	mesh->SetBuffer("in_TexCoord", objTexCoords);
}
