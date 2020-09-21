#include "RendererComponent.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Core.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"
#include "ShaderProgram.h"

void RendererComponent::onDisplay()
{
	if (!shader && mesh && tex) //TODO Rewrite this and ShaderProgram to allow for Camera instance
	{
		getCore()->getShaderProgram()->draw(mesh, tex, getCore()->getCamera(), getEntity(), NULL);
	}
	else
	{
		if (mesh && tex)
			shader->draw(mesh, tex, getCore()->getCamera(), getEntity(), shader->GetId());
	}
}

void RendererComponent::setShader(const std::string& _vert, const std::string& _frag)
{
	shader = std::make_shared<ShaderProgram>(_vert, _frag);
}

void RendererComponent::setMesh(const std::string& _path)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, _path.c_str(), "./Assets/Models/", true);

	if (!warn.empty())
		std::cout << warn << std::endl;

	if (!err.empty())
		throw std::runtime_error(err);

	if (!ret)
		throw std::runtime_error("Failed to load model");

	objPositions = std::make_shared<VertexBuffer>();
	objNormals = std::make_shared<VertexBuffer>();
	objTexCoords = std::make_shared<VertexBuffer>();
	mesh = std::make_shared<VertexArray>();

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
				objPositions->add(glm::vec3(vx, vy, vz));
				tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
				tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
				tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
				objNormals->add(glm::vec3(nx, ny, nz));
				tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
				tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
				objTexCoords->add(glm::vec2(tx, ty));
			}
			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}

	// Append `default` material
	materials.push_back(tinyobj::material_t());

	for (size_t m = 0; m < materials.size(); m++) {
		tinyobj::material_t* mp = &materials[m];
		if (mp->diffuse_texname.length() > 0)
			tex = texture->loadTexture("Assets/Textures/" + mp->diffuse_texname);
	}

	mesh->SetBuffer("in_Position", objPositions);
	mesh->SetBuffer("in_Normal", objNormals);
	mesh->SetBuffer("in_TexCoord", objTexCoords);
}